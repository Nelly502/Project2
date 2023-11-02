#pragma once
#include <map>
#include "Singleton.h"

#include "GameObject/TextureManager.h"


class ResourceManagers : public CSingleton<ResourceManagers>
{
public:
	ResourceManagers();
	~ResourceManagers();


	void AddTexture(const std::string& name);
	void AddFont(const std::string& name);

	void RemoveSound(const std::string& name) {};
	void RemoveTexture(const std::string& name);
	void RemoveFont(const std::string& name);

	std::shared_ptr<TextureManager> GetTexture(const std::string& name);
	bool Play1Win = false;
	bool Play2Win = false;
	void set_Play1Win(bool on);
	bool get_Play1Win();

	void set_Play2Win(bool on);
	bool get_Play2Win();
	bool on_Music = true;
	void set_Music(bool on);
	bool get_Music();
	int demWin1 = 0;
	int demWin2 = 0;
	
private:
	std::map<std::string, std::shared_ptr<TextureManager>> m_MapTexture;
	std::string m_ShaderPath;
	std::string m_TexturePath;
	std::string m_ModelsPath;
	std::string m_FontPath;

	//Sound
	std::string m_SoundPath;
	
	//bool on_Music = true;
	
	
};
