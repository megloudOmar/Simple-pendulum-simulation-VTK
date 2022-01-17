#include <vtkCommand.h>
#include <vtkActor.h>
#include "Manager.h"

extern const double PI;				// PI value
extern const float lambda;
extern float length;
extern const float	theta_0_rad;
extern float T;

class Timer : public vtkCommand
{
public:
    Timer() = default;

    static Timer* New()
    {
        Timer* cb = new Timer;
        cb->TimerCount = 0;
        return cb;
    }
    void Execute(vtkObject*, unsigned long, void*);
	// functions
    float theta_t(float theta_0, float T, float t);
    float theta_t_d(float theta_0, float T, float lambda, float t);
    float radian_to_degree(float radian);
    float degree_to_radian(float degree);
	
	void SetManager(Manager* m) { 
        m_t = m;
    }

private:
    int TimerCount = 0;

public:
    vtkActor* cylinder = nullptr;
    vtkActor* sphere = nullptr;
    int maxCount = -1;
    int timerId = 0;
	Manager* m_t;

};
