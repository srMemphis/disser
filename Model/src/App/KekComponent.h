#pragma once
#include <FMEngine.h>

class KekComponent : public Component
{
public:
	KekComponent();
	~KekComponent();

	virtual void OnGuiRender() override;
private:
};

