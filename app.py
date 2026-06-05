from flask import Flask, render_template, request, redirect, url_for
from flask import send_file
from reportlab.pdfgen import canvas
import os
import subprocess

app = Flask(__name__)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

UPLOAD_FOLDER = os.path.join(BASE_DIR, "uploads")
OUTPUT_FOLDER = os.path.join(BASE_DIR, "output")
ANALYSIS_FOLDER = os.path.join(BASE_DIR, "analysis")

os.makedirs(UPLOAD_FOLDER, exist_ok=True)
os.makedirs(OUTPUT_FOLDER, exist_ok=True)

@app.route("/")
def home():
    return render_template("index.html")


@app.route("/upload")
def upload():
    return render_template("upload.html")


@app.route("/analyze", methods=["POST"])
def analyze():

    files = request.files.getlist("files")

    if len(files) == 0:
        return "No files selected"

    # Clear uploads folder
    for filename in os.listdir(UPLOAD_FOLDER):

        filepath = os.path.join(
            UPLOAD_FOLDER,
            filename
        )

        try:
            if os.path.isfile(filepath):
                os.remove(filepath)

        except Exception as e:
            print("Delete Error:", e)

    # Save uploaded files
    saved_count = 0

    for file in files:

        if file.filename.strip() != "":

            save_path = os.path.join(
                UPLOAD_FOLDER,
                file.filename
            )

            file.save(save_path)
            saved_count += 1

    if saved_count == 0:
        return "No valid files uploaded"

    exe_path = os.path.join(
        ANALYSIS_FOLDER,
        "maulik.exe"
    )

    if not os.path.exists(exe_path):

        return f"""
        maulik.exe not found

        <br><br>

        Expected Location:

        <br>

        {exe_path}
        """

    try:

        subprocess.run(
            [exe_path],
            cwd=ANALYSIS_FOLDER,
            check=True
        )

    except subprocess.CalledProcessError as e:

        return f"""
        Analysis Engine Failed

        <br><br>

        {e}
        """

    except Exception as e:

        return f"""
        Unexpected Error

        <br><br>

        {e}
        """

    return redirect(url_for("dashboard"))


@app.route("/dashboard")
def dashboard():

    dashboard_file = os.path.join(
        OUTPUT_FOLDER,
        "dashboard_data.txt"
    )

    ai_file = os.path.join(
        OUTPUT_FOLDER,
        "ai_insight.txt"
    )

    report_file = os.path.join(
        OUTPUT_FOLDER,
        "report.txt"
    )

    totalFiles = "0"
    totalComparisons = "0"
    highRisk = "0"
    moderateRisk = "0"
    lowRisk = "0"

    if os.path.exists(dashboard_file):

        with open(
            dashboard_file,
            "r"
        ) as f:

            data = f.read().splitlines()

            if len(data) >= 5:

                totalFiles = data[0]
                totalComparisons = data[1]
                highRisk = data[2]
                moderateRisk = data[3]
                lowRisk = data[4]

    insight = ""

    if os.path.exists(ai_file):

        with open(
            ai_file,
            "r"
        ) as f:

            insight = f.read()

    report = ""

    if os.path.exists(report_file):

        with open(
            report_file,
            "r"
        ) as f:

            report = f.read()

    return render_template(
        "dashboard.html",
        totalFiles=totalFiles,
        totalComparisons=totalComparisons,
        highRisk=highRisk,
        moderateRisk=moderateRisk,
        lowRisk=lowRisk,
        insight=insight,
        report=report
    )


@app.route("/report")
def report():

    report_file = os.path.join(
        OUTPUT_FOLDER,
        "report.txt"
    )

    report_data = ""

    if os.path.exists(report_file):

        with open(
            report_file,
            "r"
        ) as f:

            report_data = f.read()

    return render_template(
        "report.html",
        report=report_data
    )
    
@app.route("/download_pdf")   
def download_pdf():

    report_file = os.path.join(
        OUTPUT_FOLDER,
        "report.txt"
    )

    pdf_file = os.path.join(
        OUTPUT_FOLDER,
        "report.pdf"
    )
    from reportlab.pdfgen import canvas
    c = canvas.Canvas(pdf_file)

    y = 800

    with open(report_file, "r") as f:

        for line in f:

            c.drawString(
                40,
                y,
                line.strip()
            )

            y -= 15

            if y < 40:
                c.showPage()
                y = 800

    c.save()

    return send_file(
        pdf_file,
        as_attachment=True
    )


if __name__ == "__main__":

    app.run(
        host="127.0.0.1",
        port=5000,
        debug=True
    )