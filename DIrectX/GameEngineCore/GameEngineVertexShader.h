#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"

// Ό³Έν :
class GameEngineVertexShader : public GameEngineResources<GameEngineVertexShader>, public GameEngineShader
{
	friend class GameEngineInputLayOut;

public:
	// constrcuter destructer
	GameEngineVertexShader();
	~GameEngineVertexShader();

	// delete Function
	GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineVertexShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		return Load(_Path, _EntryPoint, _EntryPoint, _VersionHigh, _VersionLow);
	}

	static std::shared_ptr<GameEngineVertexShader> Load(std::string_view _Path, std::string_view _Name, std::string_view _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEngineVertexShader> Res = GameEngineVertexShader::CreateRes(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	void Setting();

protected:

private:
	ID3D11VertexShader* ShaderPtr = nullptr;

	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

};

