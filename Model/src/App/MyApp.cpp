#include "MyApp.h"
#include "KekComponent.h"
#include "RenderComponent.h"


#include <iostream>

MyApp::MyApp()
	: App()
{
	m_ComponentList.AddComponent(new KekComponent());
	//m_ComponentList.AddComponent(new RenderComponent());
}

MyApp::~MyApp()
{
}
