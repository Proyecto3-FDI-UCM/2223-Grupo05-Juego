#pragma once
#include "Component.h"
#ifdef _JUEGODLL
#define JUEGO_API  __declspec(dllexport)
#else
#define JUEGO_API  __declspec(dllimport)
#endif // _JUEGODLL

 class PlayerController : public LocoMotor::Component
{
public:
	PlayerController();
	virtual ~PlayerController();
	void Init(std::vector<std::pair<std::string, std::string>>& params) override;
	void Update(float dt)override;
	void InitComponent() override;
};
