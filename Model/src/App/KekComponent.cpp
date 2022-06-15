#include "KekComponent.h"

KekComponent::KekComponent()
{
}

KekComponent::~KekComponent()
{
}

void KekComponent::OnGuiRender()
{
	bool show = true;
	ImGui::ShowDemoWindow(&show);
}
