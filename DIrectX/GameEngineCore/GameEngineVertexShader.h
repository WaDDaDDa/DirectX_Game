#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"

// 설명 :                              다중 상속
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

	static std::shared_ptr<GameEngineVertexShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		return Load(_Path, _EntryPoint, _EntryPoint, _VersionHight, _VersionLow);
	}

	static std::shared_ptr<GameEngineVertexShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEngineVertexShader> Res = GameEngineVertexShader::CreateRes(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHight, _VersionLow);
		return Res;
	}

	void Setting();

protected:

private:
	std::string EntryName = "";
	ID3D11VertexShader* ShaderPtr = nullptr;

	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0);

};

