#include "pch.h"
#include "GreetingScene.h"

GreetingScene::GreetingScene()
{
	LoadResources();
	Sounds::PlayAt(SoundId::Greeting);
}

void GreetingScene::LoadResources()
{
	const auto windowFrame = Window::Instance().GetWindowFrame();

	rememberNote = std::make_unique<Sprite>( TextureId::Warning, windowFrame );
}

void GreetingScene::Update(float dt)
{
	if (Sounds::IsPlayingAt(SoundId::Greeting) == false)
		SceneManager::Instance().SetScene(Scene::Charleston);
}

void GreetingScene::Draw()
{
	rememberNote->Draw( Vector2{ 0.0f, 0.0f } );
}

void GreetingScene::OnKeyDown(BYTE keyCode)
{
	switch (keyCode)
	{
		case VK_ESCAPE:
		case VK_RETURN:
		case VK_SPACE:
			Sounds::StopAt(SoundId::Greeting);
			break;
	}
}
