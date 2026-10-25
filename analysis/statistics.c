#include "statistics.h" 

void calculateStatistics(
    float similarities[],
    int count,
    int *high,
    int *moderate,
    int *low
)
{
    int i;

    *high = 0;
    *moderate = 0;
    *low = 0;

    for(i = 0; i < count; i++)
    {
        if(similarities[i] >= 60)
        {
            (*high)++;
        }
        else if(similarities[i] >= 30)
        {
            (*moderate)++;
        }
        else
        {
            (*low)++;
        }
    }
}
