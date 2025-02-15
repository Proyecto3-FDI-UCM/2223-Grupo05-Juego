#pragma once
#include "Component.h"

namespace LocoMotor {
	class UIImageLM;
	class UITextLM;
}
namespace JuegoDeAutos {
	class RaceManager;

	class SceneChangeButton : public LocoMotor::Component {
	public:
		SceneChangeButton();
		~SceneChangeButton();
		void Start() override;
	private:
		/// @brief Changes the text of the UI 
		void ChangeVelocity();

		LocoMotor::UIImageLM* _raceButton;
		LocoMotor::UIImageLM* _speedButton;
		LocoMotor::UITextLM* _speedText;
	};
}

