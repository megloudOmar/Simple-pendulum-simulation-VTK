#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include "Timer.h"

/*
function that calculates the angle as a function of time according to the motion equation solution: θ(t)=θo*cos(ω*t)
inputs:
	theta_0 :	initial angular displacement
	T	    :	period of oscillation
	t		:	time
*/
float Timer::theta_t(float theta_0, float T, float t)
{
	float theta_t = theta_0 * cos((2 * PI / T) * t);
	return theta_t;
}
// Osccilation with damping 
// θ(t)=θo*exp(−λ*ω*t)*cos(sqrt(1−λ²)*ω*t)
float Timer::theta_t_d(float theta_0, float T, float lambda, float t)
{
	float theta_t = theta_0 * exp(-lambda*(2 * PI / T)*t) * cos(sqrt(1-(lambda * lambda))* (2 * PI / T)*t);
	return theta_t;
}


/*
function that converts the angle from radian to degree
inputs:
	radian	:	angle in radian
*/
float Timer::radian_to_degree(float radian)
{
	return (radian * (180 / PI));
}
/*
function that converts the angle from radian to degree
inputs:
	radian	:	angle in degree
*/
float Timer::degree_to_radian(float degree)
{
	return (degree * (PI / 180));
}

void Timer::Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData))
{
	// start simulation if 's' is pressed
	if (this-> m_t->enable==1)
	{
		if (vtkCommand::TimerEvent == eventId)
		{
			// Increment timer
			++this->TimerCount;
		}
		float angle = 0.0;
		float t = 0.0;
		// Division of TimerCount to obtain a small time variation
		t = static_cast<float>(this->TimerCount) / 10.0;
		// Calculate the angle
		if (this->m_t->angle == 1)
		{
			angle = theta_t(theta_0_rad, T, t);
		}
		else if (this->m_t->angle == 2)
		{
			angle = theta_t_d(theta_0_rad, T, lambda, t);
		}
		// angle = theta_t(theta_0_rad, T, t);
		// polar coordinates to cartesian coordinates 
		// sin(angle) = x / length
		// cos(angle) = y / length
		sphere->SetPosition((double)length * sin(angle), double(length) - (double)(length * cos(angle)), 0.0);
		// z-axis rotation of the cylinder 
		cylinder->SetOrientation(0.0, 0.0, radian_to_degree(angle));
		std::cout << "xxxxx" << std::endl;
		// radian to degree conversion
		std::cout << radian_to_degree(angle) << std::endl;
		std::cout << this->TimerCount << std::endl;

		if (this->TimerCount < this->maxCount)
		{

			vtkRenderWindowInteractor* iren =
				dynamic_cast<vtkRenderWindowInteractor*>(caller);
			iren->GetRenderWindow()->Render();
		}
		else
		{
			vtkRenderWindowInteractor* iren =
				dynamic_cast<vtkRenderWindowInteractor*>(caller);
			if (this->timerId > -1)
			{
				iren->DestroyTimer(this->timerId);
			}
		}
	}
}
