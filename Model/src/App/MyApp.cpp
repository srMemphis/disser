#include "MyApp.h"
#include "KekComponent.h"


#include <iostream>

MyApp::MyApp()
	: App()
{
	m_ComponentList.AddComponent(new KekComponent());
}

MyApp::~MyApp()
{
}
