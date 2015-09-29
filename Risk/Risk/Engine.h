#pragma once
class Engine
{
private:
	void reinforcementPhase();
	void attackPhase();
	void fortificationPhase();
public:
	Engine();
	~Engine();
	void startPhase();
	void gamePlayPhase();

};

