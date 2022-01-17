#include <vtkCommand.h>
#include <vtkConeSource.h>
#include "Manager.h"

class Observer : public vtkCommand {
public:
    static Observer* New() { return new Observer; }
    void Execute(vtkObject*, unsigned long, void*);
	void SetManager(Manager* m) { 
        m_o = m;
    }

	Manager* m_o;
} ;