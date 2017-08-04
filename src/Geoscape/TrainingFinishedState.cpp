/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "TrainingFinishedState.h"
#include "../Engine/Game.h"
#include "../Engine/LocalizedText.h"
#include "../Mod/Mod.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Interface/TextList.h"
#include "../Savegame/Soldier.h"
#include "AllocateTrainingState.h"
#include "../Engine/Options.h"

namespace OpenXcom
{
/**
 * Initializes all the elements in the TrainingFinished screen.
 * @param base Pointer to the base to get info from.
 * @param list List of soldiers who finished their training
 */
TrainingFinishedState::TrainingFinishedState(Base *base, const std::vector<Soldier *> & list) : _base(base)
{
	_screen = false;

	// Create objects
	_window = new Window(this, 288, 180, 16, 10);
	_btnOk = new TextButton(160, 14, 80, 149);
	_btnOpen = new TextButton(160, 14, 80, 165);
	_txtTitle = new Text(288, 40, 16, 20);
	_lstPossibilities = new TextList(250, 80, 35, 50);

	// Set palette
	setInterface("geoManufacture");

	add(_window, "window", "geoManufacture");
	add(_btnOk, "button", "geoManufacture");
	add(_btnOpen, "button", "geoManufacture");
	add(_txtTitle, "text1", "geoManufacture");
	add(_lstPossibilities, "text2", "geoManufacture");

	centerAllSurfaces();

	// Set up objects
	_window->setBackground(_game->getMod()->getSurface("BACK02.SCR"));

	_btnOk->setText(tr("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&TrainingFinishedState::btnOkClick);
	_btnOk->onKeyboardPress((ActionHandler)&TrainingFinishedState::btnOkClick, Options::keyCancel);
	_btnOpen->setText(tr("STR_TRAINING"));
	_btnOpen->onMouseClick((ActionHandler)&TrainingFinishedState::btnOpenClick);
	_btnOpen->onKeyboardPress((ActionHandler)&TrainingFinishedState::btnOpenClick, Options::keyOk);
	_btnOpen->setVisible(Options::anytimeMartialTraining);
	_txtTitle->setBig();
	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setText(tr("STR_TRAINING_FINISHED"));

	_lstPossibilities->setColumns(1, 250);
	_lstPossibilities->setBig();
	_lstPossibilities->setAlign(ALIGN_CENTER);
	_lstPossibilities->setScrolling(true, 0);
	for (std::vector<Soldier *>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		_lstPossibilities->addRow (1, (*iter)->getName().c_str());
	}
}

/**
 * Closes the screeen.
 * @param action Pointer to an action.
 */
void TrainingFinishedState::btnOkClick(Action *)
{
	_game->popState();
}

/**
 * Opens the AllocateTrainingState.
 * @param action Pointer to an action.
 */
void TrainingFinishedState::btnOpenClick(Action *)
{
	_game->popState();
	_game->pushState(new AllocateTrainingState(_base));
}

}
