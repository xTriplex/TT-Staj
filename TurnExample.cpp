#include <iostream>
#include <algorithm>
#include <vector>

class Character
{
public:
  Character(std::string name, int baseSpeed, bool isEnemy = false)
      : name(name), baseSpeed(baseSpeed), isEnemy(isEnemy)
  {
    reset();
  }

  // TODO: Calculate buffs from other characters, relics and lightcones.
  void increaseSpeed(int amount)
  {
    baseSpeed += amount;
    reset();
  }

  // TODO: Calculate buffs from other characters, relics and lightcones.
  void applyActionAdvance(double percentage)
  {
    currentActionValue -= static_cast<int>(baseActionValue * percentage);
  }

  // TODO: Calculate buffs from other characters, relics and lightcones.
  void applyActionDelay(double percentage)
  {
    currentActionValue += static_cast<int>(baseActionValue * percentage);
  }

  void updateActionValue(int passedTime);

  void reset()
  {
    baseActionValue = 10000 / baseSpeed;
    currentActionValue = baseActionValue;
  }

  int getBaseSpeed() const
  {
    return baseSpeed;
  }

  int getAttacksInCycle() const
  {
    return attacksInCycle;
  }

  void resetAttacksInCycle()
  {
    attacksInCycle = 0;
  }

  std::string getName() const
  {
    return name;
  }

  int getCurrentActionValue() const
  {
    return currentActionValue;
  }

  bool isEnemyCharacter() const
  {
    return isEnemy;
  }

private:
  std::string name;
  int baseSpeed;
  int baseActionValue;
  int currentActionValue;
  bool isEnemy;
  int attacksInCycle = 0;
};

void Character::updateActionValue(int passedTime)
{
  currentActionValue -= passedTime;
  if (currentActionValue <= 0)
    {
      if (!isEnemy)
        {
          attacksInCycle++;
        }
      reset();
    }
}

bool compareSpeed(const Character &a, const Character &b)
{
  return a.getBaseSpeed() > b.getBaseSpeed();
}

void addCharacter(std::vector<Character> &characters)
{
  if (characters.size() >= 4)
    {
      std::cout << "You've already added the maximum number of characters.\n";
      return;
    }
  std::string name;
  int speed;
  std::cout << "Enter the name of the character: ";
  std::getline(std::cin >> std::ws, name);
  std::cout << "Enter the speed of the character: ";
  std::cin >> speed;
  std::cout << "Name: " << name << ", Speed: " << speed
            << std::endl; // Debug print statement
  characters.push_back(Character(name, speed));
  std::cout << "Character added successfully!\n";
}

void printCharacters(const std::vector<Character> &characters)
{
  std::cout << "Characters:\n";
  for (const Character &character : characters)
    {
      std::cout << character.getName()
                << " (Speed: " << character.getBaseSpeed() << ")\n";
    }
}

int main ()
{
  std::vector<Character> characters;
  bool quit = false;
  while (!quit)
    {
      std::cout << "\nMenu:\n"
                << "0 - Quit\n"
                << "1 - Add Character\n"
                << "Choose an option: ";
      int choice;
      std::cin >> choice;
      switch (choice)
        {
        case 0:
          quit = true;
          break;
        case 1:
          addCharacter (characters);
          if (characters.size() >= 4)
            {
              quit = true;
            }
          break;
        default:
          std::cout << "Invalid option. Please choose again.\n";
          break;
        }
    }

  if (characters.empty())
    {
      std::cout << "No characters added. Exiting.\n";
      return 0;
    }
  // You can manually add your own enemies to test.
  Character warpTrotter("Warp Trotter", 83, true);
  Character frigidProwler("Frigid Prowler", 100, true);
  Character automatonGrizzly("Automaton Grizzly", 120, true);
  Character automatonDirewolf("Automaton Direwolf", 144, true);

  characters.push_back(warpTrotter);
  characters.push_back(frigidProwler);
  characters.push_back(automatonGrizzly);
  characters.push_back(automatonDirewolf);

  std::sort (characters.begin(), characters.end(), compareSpeed);

  // Output the number of attacks each character can make in a cycle
  for (Character &character : characters)
    {
      character.resetAttacksInCycle(); // Reset attacks in cycle before counting
    }

  // Display each character's turn alongside their action value and speed
  for (int i = 0; i < characters.size(); i++)
    {
      // Output turn notifications for this cycle
      std::cout << "##########################\n    "
                << characters[i].getName()
                << "'s Turn   \n##########################\n";

      // Update action values for all characters
      for (int j = 0; j < characters.size(); j++)
        {
          if (i == j)
            {
              characters[j].resetAttacksInCycle(); // Reset attacks in cycle for the current character
            }
          else
            {
              int passedTime = characters[i].getCurrentActionValue(); // Subtracting current character's action value just like in the game
              characters[j].updateActionValue(passedTime); // Update action value for each character
            }
        }

      // Output stats for all characters
      for (const Character &character : characters)
        {
          std::cout << character.getName() << "'s stats: |Action Value: "
                    << (character.getName() == characters[i].getName()
                            ? 0
                            : character.getCurrentActionValue())
                    << "| |Speed: " << character.getBaseSpeed() << "| \n";
        }
    }
  // Output the number of attacks each character can make in a cycle
  std::cout << "\nAttacks per cycle:\n";
  for (const Character &character : characters)
    {
      if (!character.isEnemyCharacter())
        {
          std::cout << character.getAttacksInCycle() << " attacks by "
                    << character.getName() << '\n';
        }
    }
  return 0;
}
