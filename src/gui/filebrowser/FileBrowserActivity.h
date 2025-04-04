#pragma once

#include "common/String.h"
#include "Activity.h"
#include "tasks/TaskListener.h"

#include <vector>
#include <functional>
#include <memory>

class SaveFile;

namespace ui
{
	class Label;
	class ScrollPanel;
	class ProgressBar;
}

class LoadFilesTask;
class FileBrowserActivity: public TaskListener, public WindowActivity
{
	using OnSelected = std::function<void (std::unique_ptr<SaveFile>)>;

	LoadFilesTask * loadFiles;
	OnSelected onSelected;
	ui::ScrollPanel * itemList;
	ui::Label * infoText;
	std::vector<std::unique_ptr<SaveFile>> files;
	bool createButtons = false;
	std::vector<ui::Component*> components;
	std::vector<ui::Component*> componentsQueue;
	ByteString directory;
	bool hasQueuedSearch;
	ByteString queuedSearch;

	ui::ProgressBar * progressBar;

	int totalFiles;
	int filesX, filesY, buttonPadding;
	int fileX, fileY;
	int buttonWidth, buttonHeight, buttonAreaWidth, buttonAreaHeight, buttonXOffset, buttonYOffset;

	void populateList();
	void cleanup();
public:
	FileBrowserActivity(ByteString directory, OnSelected onSelected = nullptr);
	virtual ~FileBrowserActivity();
	
	void OnDraw() override;
	void OnTick() override;
	void OnTryExit(ExitMethod method) override;
	void OnMouseDown(int x, int y, unsigned button) override;
	void loadDirectory(ByteString directory, ByteString search);
	void SelectSave(int index);
	void DeleteSave(int index);
	void RenameSave(int index);
	void DoSearch(ByteString search);

	void NotifyDone(Task * task) override;
	void NotifyError(Task * task) override;
	void NotifyProgress(Task * task) override;
	void NotifyStatus(Task * task) override;
};
