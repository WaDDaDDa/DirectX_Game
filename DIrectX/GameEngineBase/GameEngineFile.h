#pragma once
#include "GameEnginePath.h"
#include "GameEngineSerializer.h"
#include <string>

// Ostream Istream 도 비슷한 방식이다.

enum class FileOpenType
{
	Write,
	Read,
};

enum class FileDataType
{
	Binary,
	Text,
};

// 설명 :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const std::string& _path);
	~GameEngineFile();

	//// delete Function
	//GameEngineFile(const GameEngineFile& _Other) = delete;
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	//GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

	// 운영체제에게 허락을 맡아서 이 파일을 이제부터 편집하거나 읽겠습니다.
	void Open(FileOpenType _OpenType, FileDataType _DataType, bool _IsStartAllData = true);

	// 파일에서 데이터를 읽어드린다.
	void Read(void* _Data, size_t _Size);

	// 파일에서 데이터를 쓴다.
	void Write(void* _Data, size_t _Size);

	// 8바이트 정수형
	template<typename ReturnType>
	ReturnType GetFileSize()
	{
		return static_cast<ReturnType>(GetFileSize());
	}

	uintmax_t GetFileSize();

	std::string_view GetStringView();
protected:

private:
	FILE* FilePtr = nullptr;
	FileOpenType OpenType;
	FileDataType DataType;
	GameEngineSerializer Serializer;
};

