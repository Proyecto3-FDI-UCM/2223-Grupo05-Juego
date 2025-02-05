#pragma once
#include "Component.h"
#include "LMVector.h"

namespace LocoMotor {
	class RigidBody;
	class InputManager;
	class MeshRenderer;
	class UITextLM;
	class Camera;
}

namespace JuegoDeAutos {
	class RaceManager;

	class PlayerController : public LocoMotor::Component
	{
	public:
		PlayerController();
		virtual ~PlayerController();

		void InitComponent() override;


		void Start()override;
		/// @brief Updates the component 
		/// @param dt delta time
		void Update(float dt)override;


		// Movimiento de la nave

		// Actualiza la direccion Up del componente Transform para que la nave siempre se posicione
		// a la misma distancia y direccion de la carretera respetando su rotacion
		// Esto es necesario para que la nave se quede "pegada" a la carretera en todo momento

		/// @brief Updates the direcction Up of the Transform component, so the ship is always at the
		/// same distance and rotation 
		/// @param dt delta time 
		void UpdateUpDirection(float dt);

		// Almacena el input de esta ejecucion

		/// @brief Gets the input on that frame
		void GetInput();

		// Metodos que se encargan de la gestion del movimiento linear/angular
		// Se encargan de llamar a los metodos de movimiento de forma ordenada y controlada

		/// @brief Moves the ship using linear forces
		void MoveShip(float dt);
		/// @brief Moves the ship using angular forces
		void TurnShip(float dt);

		// Dependiendo del Input recogido, estos metodos aplican fuerzas al rigidbody de la nave

		/// @brief Applies linear force
		/// @param dt delta time
		void ApplyLinearForces(float dt);
		/// @brief Applies angular force
		/// @param dt delta time
		void ApplyAngularForces(float dt);

		// Estos metodos se encargan de aplicar un Drag linear/angular, para que el movimiento de la 
		// nave se sienta mas controlado y mejorar la experiencia de jugador

		/// @brief Applies a linear drag
		/// @param dt delta time
		void LinearDrag(float dt);
		/// @brief Applies an angular drag
		/// @param currentAngularVelocity Current angular velocity
		/// @param direction Current direction 
		void AngularDrag(LocoMotor::LMVector3 currentAngularVelocity, int direction);

		// Este metodo se encarga de inclinar levemente el componente MeshRenderer hacia los lados 
		// dependiendo de la rotacion actual de la nave (puramente estetico)

		/// @brief Tilts the mesh renderer depending on the actual rotation
		/// @param currentAngularVelocity Current angular velocity
		/// @param direction Current direction 
		void TiltShip(float currentAngularVelocity, int direction);

		// Limita la velocidad maxima angular para que el coche no pueda girar rapidisimo
		/// @brief Limits the maximum angular velocity 
		/// @param currentAngularVelocity Current angular velocity
		/// @param direction Current direction 
		void LimitMaxAngleVelocity(LocoMotor::LMVector3 currentAngularVelocity, int direction);
		/// @brief Sets the FOV of the camera according to the velocity of the ship
		void AdjustFov();
		/// @brief Checks and respawns the ship on the last checkpoint if it goes under the water
		void CheckRespawn();

		/// @brief Updates the text and the color of the velocity text on the UI
		void UpdateVelocityUI();

		/// @brief Enables the gyroscope
		void EnableGyro();
		/// @brief Disables the gyroscope
		void DisableGyro();
		/// @brief Sets a new acceleration force
		/// @param newAcceleration The acceletration
		void SetAcceleration(float newAcceleration);

		/// @brief Enables or disables input for the ship
		/// @param controllable True if the ship is controllable
		void SetControllable(bool controllable);

		void OnCollisionEnter(LocoMotor::GameObject* other) override;

	private:

		// Referencias
		RaceManager* raceManager;
		LocoMotor::RigidBody* rbComp;
		LocoMotor::MeshRenderer* meshComp;
		LocoMotor::InputManager* inputMng;
		LocoMotor::UITextLM* velocityText;
		LocoMotor::Camera* cam;

		// Paremetros de movimiento
			// Fisicas
		float acceleration = 1000;
		float reversingAcceleration = -800;
		float maxAngularVelocity = 4;
		float angularForce = .5f;
		float angularDragForce = .6f;
		float linearDragForce = 40;
		float gravityThrust = -1600;
			// Matematicas
				// Linear
				
				// Rotacion
		float currentRotationVelocity = 0;
		float maxRotationVelocity = .1f;
		float rotationAcceleration = .01f;
		float rotationDecceleration = .02f;

		// Controles
		float extraAceleration = 30;
		float joystickDeadzone = .05f;
		bool useGyro = false;
		float maxGyroValue = 8;

		// Fov
		float initialFov = 60;
		float maxExtraFov = 15;

		// Almacenar informacion
			// Controles
				// Devuelve true si en esta ejecucion se tiene presionado el boton de acelerar (mando o teclado)
		bool accelerate;
		bool reverseAccelerate;
		bool turnRight;
		bool turnLeft;
		float joystickValue;
		float accTriggerValue;
		float reverseAccTriggerValue;
		float gyroValue;

		// Devuelve true si se esta girando
		bool turning;
		bool inAir;
		bool inAirLastFrame;

			// Guarda la intensidad del drag en cada momento para usarlo como aceleracion extra
		float linearDragIntensity;

		bool physicsBasedMovement = true;

		bool activeInput = false;
	};
}