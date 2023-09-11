#pragma once

class FileManager
{
public:
	// Constructor Destructor
	FileManager();
	~FileManager();

	// Delete Function
	FileManager(const FileManager& _Other) = delete;
	FileManager(FileManager&& _Other) noexcept = delete;
	FileManager& operator=(const FileManager& _Other) = delete;
	FileManager& operator=(FileManager&& _Other) noexcept = delete;

	static void FileLoad(int Max, std::vector<unsigned int>& IndexData);
	static void FileSave(int Max, std::vector<unsigned int>& IndexData);

protected:

private:

};