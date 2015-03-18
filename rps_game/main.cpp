/***************************************************************************
 * rps_game - Rock, Paper, Scissors Game                                   *
 *                                                                         *
 * Copyright (C) 2015  PLLUG.Community   (info@pllug.org.ua)               *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

#include <iostream>
#include <algorithm>
#include <ctime>
/*!
 * \brief The Level enum
 */
enum Level
{
    UNSPECIFIED = 0,
    EASY,
    NORMAL,
    HARD
};
/*!
 * \brief The Figure enum
 */
enum Figure
{
    UNDEF = 0,
    ROCK,
    PAPER,
    SCISSORS
};

const std::string cArgKeyLevel = "--level";
const std::string cArgKeyVersion = "--version";

const std::string cLevelStringEasy = "easy";
const std::string cLevelStringNormal = "normal";
const std::string cLevelStringHard = "hard";

const std::string cFigureStringRock = "rock";
const std::string cFigureStringPaper = "paper";
const std::string cFigureStringScissors = "scissors";

const std::string cVersionDescription = "Version 2.0. Short description.";

const std::string cErrorMessage = "Error. Wrong input.";

/*!
 * \brief showHelp
 */
void showHelp()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "  rps_game [options]" << std::endl;
    std::cout << "      --level (EASY|NORMAL|HARD)" << std::endl;
    std::cout << "          specify game difficulty (argument is required)" << std::endl;
    std::cout << "      --version" << std::endl;
    std::cout << "          output programm version" << std::endl;
}

/*!
 * \brief parseLevel
 * \param levelString
 * \return
 */
Level parseLevel(std::string levelString)
{
    Level rLevel = UNSPECIFIED;

    std::transform(levelString.begin(), levelString.end(), levelString.begin(), ::tolower);

    if (cLevelStringEasy == levelString)
    {
        rLevel = EASY;
    }
    else if (cLevelStringNormal == levelString)
    {
        rLevel = NORMAL;
    }
    else if (cLevelStringHard == levelString)
    {
        rLevel = HARD;
    }

    return rLevel;
}

/*!
 * \brief parseFigure
 * \param figureString
 * \return
 */
Figure parseFigure(std::string figureString)
{
    Figure rFigure = UNDEF;

    std::transform(figureString.begin(), figureString.end(), figureString.begin(), ::tolower);

    if (cFigureStringRock == figureString)
    {
        rFigure = ROCK;
    }
    else if (cFigureStringPaper == figureString)
    {
        rFigure = PAPER;
    }
    else if (cFigureStringScissors == figureString)
    {
        rFigure = SCISSORS;
    }

    return rFigure;
}

/*!
 * \brief findArgPosition
 * \param argc
 * \param argv
 * \param argName
 * \return
 */
int findArgPosition(int argc, char* argv[], const std::string &argName)
{
    int rPosition = -1;

    for (int argIndex = 1; argIndex < argc; ++argIndex)
    {
        std::string nextArg = argv[argIndex];
        std::transform(nextArg.begin(), nextArg.end(), nextArg.begin(), ::tolower);

        if (argName == nextArg)
        {
            rPosition = argIndex;
        }
    }

    return rPosition;
}

/*!
 * \brief stringArg
 * \param argc
 * \param argv
 * \param argName
 * \return
 */
std::string stringArg(int argc, char* argv[], std::string argName)
{
    std::string result;

    int argIndex = findArgPosition(argc, argv, argName);

    if (-1 != argIndex)
    {
        if (argIndex + 1 < argc)
        {
            result = argv[argIndex + 1];
        }
    }

    return result;
}

/*!
 * \brief isVersion
 * \param argc
 * \param argv
 * \param argName
 * \return
 */
bool isVersion(int argc, char **argv, std::string argName)
{
    for(int i = 1; i < argc; i++)
    {
        if(argv[i] == argName)
        {
            std::cout << cVersionDescription << std::endl;
            return true;
        }
    }
    return false;
}

/*!
 * \brief isValid
 * \param argc
 * \param argv
 * \return
 */
bool isValid(int argc, char **argv)
{
    for(int i = 1; i < argc; i++)
    {
        std::string nextArg = argv[i];
        std::transform(nextArg.begin(), nextArg.end(), nextArg.begin(), ::tolower);
        if((nextArg == cArgKeyLevel) || (nextArg == cArgKeyVersion) || (nextArg == cLevelStringEasy)
            || (nextArg == cLevelStringNormal) || (nextArg == cLevelStringHard))
            continue;
        else
        {
            std::cout << cErrorMessage << std::endl;
            return false;
        }
    }
    return true;
}

/*!
 * \brief getFigure
 * \return
 */
Figure getFigure() {
    std::string choice;
    std::cout << "Put figure:" << std::endl;
    std::cin >> choice;
    return parseFigure(choice);
}

/*!
 * \brief getRandomFig
 * \return
 */
Figure getRandomFig() {
    return static_cast<Figure>(rand()%3 + 1);
    }

/*!
 * \brief getRandomFig
 * \param userFig
 * \param randFig
 * \return
 */
int userWin(Figure userFig, Figure randFig){
    if (userFig == randFig)
        return 0;
    switch(userFig) {
        case ROCK:
            if(randFig == PAPER)
                return -1;
            if(randFig == SCISSORS)
                return 1;
            break;
        case PAPER:
            if(randFig == ROCK)
                return 1;
            if(randFig == SCISSORS)
                return -1;
            break;
        case SCISSORS:
            if(randFig == PAPER)
                return 1;
            if(randFig == ROCK)
                return -1;
            break;
    }
}

/*!
 * \brief showFigure
 * \param figure
 * \return
 */
void showFigure(Figure figure)
{
    if (figure == ROCK)
        std::cout << cFigureStringRock << std::endl;
    else if (figure == PAPER)
        std::cout << cFigureStringPaper << std::endl;
    else if (figure == SCISSORS)
        std::cout << cFigureStringScissors << std::endl;
}

/*!
 * \brief gameResult
 * \param result
 * \return
 */
void gameResult(int result)
{
    if(result == 0)
        std::cout << "Draw." << std::endl;
    else if(result == 1)
        std::cout << "Winner." << std::endl;
    else if(result == -1)
        std::cout << "Loser." << std::endl;
}

/*!
 * \brief easyLevel
 * \return
 */
void easyLevel()
{
    static int i = 1;
    Figure figure = getFigure();
    if(figure == UNDEF)
    {
        std::cout << "Wrong figure." << std::endl;
        return;
    }
    if(i % 2 == 0)
        switch(figure)
        {
            case ROCK:
                showFigure(SCISSORS);
                gameResult(1);
                break;
            case PAPER:
                showFigure(ROCK);
                gameResult(1);
                break;
            case SCISSORS:
                showFigure(PAPER);
                gameResult(1);
                break;
        }
    else
    {
        Figure randomFig = getRandomFig();
        showFigure(randomFig);
        int result = userWin(figure, randomFig);
        gameResult(result);
    }
    i++;
}

/*!
 * \brief normalLevel
 * \return
 */
void normalLevel()
{
    Figure figure = getFigure();
    if(figure == UNDEF)
    {
        std::cout << "Wrong figure." << std::endl;
        return;
    }
    Figure randomFig = getRandomFig();
    showFigure(randomFig);
    int result = userWin(figure, randomFig);
    gameResult(result);
}

/*!
 * \brief hardLevel
 * \return
 */
void hardLevel()
{
    static int i = 1;
    Figure figure = getFigure();
    if(figure == UNDEF)
    {
        std::cout << "Wrong figure." << std::endl;
        return;
    }
    if(i % 2 == 0)
        switch(figure)
        {
            case ROCK:
                showFigure(PAPER);
                gameResult(-1);
                break;
            case PAPER:
                showFigure(SCISSORS);
                gameResult(-1);
                break;
            case SCISSORS:
                showFigure(ROCK);
                gameResult(-1);
                break;
        }
    else
    {
        Figure randomFig = getRandomFig();
        showFigure(randomFig);
        int result = userWin(figure, randomFig);
        gameResult(result);
    }
    i++;
}

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char* argv[])
{
    srand(time(0));
    char answer = 'y';
    while (tolower(answer) == 'y')
    {
        if (argc == 1)
        {
            showHelp();
            return 1;
        }
        // Checking for valid input
        if(!isValid(argc, argv))
        {
            showHelp();
            return 1;
        }
        // Search for --version
        if(isVersion(argc, argv, cArgKeyVersion))
            return 0;
        // Parse level
        Level level = UNSPECIFIED;

        std::string levelStr = stringArg(argc, argv, cArgKeyLevel);
        if (!levelStr.empty())
        {
            level = parseLevel(levelStr);
        }
        if (level == EASY)
            easyLevel();
        else if (level == NORMAL)
            normalLevel();
        else if (level == HARD)
            hardLevel();
        else if (level == UNSPECIFIED)
        {
            showHelp();
            return 1;
        }
        std::cout << "One more? (Y/N)" << std::endl;
        std::cin >> answer;
    }
    return 0;
}
