#pragma once

class GlobalLoad
{
public:
	// Constructor Destructor
	GlobalLoad();
	~GlobalLoad();

	// Delete Function
	GlobalLoad(const GlobalLoad& _Other) = delete;
	GlobalLoad(GlobalLoad&& _Other) noexcept = delete;
	GlobalLoad& operator=(const GlobalLoad& _Other) = delete;
	GlobalLoad& operator=(GlobalLoad&& _Other) noexcept = delete;

	static void LoadSpriteSingle(std::string_view _FileName, std::string_view _FilePath);
	static void LoadSpriteCut(int _IndexX, int _IndexY, std::string_view _FileName, std::string_view _FilePath);
	static void LoadSound(std::string_view _FileName, std::string_view _FilePath);
protected:

private:

};