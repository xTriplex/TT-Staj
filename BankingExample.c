#include <stdio.h>

typedef struct
{
    const char correctUsername[25];
    const char correctPassword[10];
    char enteredUsername[25];
    char enteredPassword[10];
    int choice;
} UserInfo;

int IsInt(const char str[]);
int StringLength(const char str[]);
void PromptUsername(char username[], int size);
void PromptPassword(char password[]);
void PrintBankMenu();
void ProcessBankMenu(int choice);
int StringCompare(const char str1[], const char str2[]);
void CapitalizeWords(char str[]);
void DeCapitalizeWords(char str[]);
int IsUpperLower(const char c);
int UpperCase(const char c);
int LowerCase(const char c);
int ContainsSpace(const char c);
void ValidateAndProcessLogin(UserInfo* userInfo);
void Deposit(int* balance);
void Withdraw(int* balance);
int GetBankChoice();

int main(void)
{
  UserInfo userInfo = {"kaan ayyildiz", "1234", "", "", 0};
  PromptUsername(userInfo.enteredUsername, sizeof(userInfo.enteredUsername));
  PromptPassword(userInfo.enteredPassword);
  ValidateAndProcessLogin(&userInfo);

  return 0;
}

int IsInt(const char str[])
{
  size_t i = 0;
  while(str[i] != '\0')
    {
      if(str[i] < '0' || str[i] > '9')
      {
        return 0;
      }
      i++;
    }
  return 1;
}

int StringLength(const char str[])
{
  size_t m_length = 0;
  while(str[m_length] != '\0')
    {
      m_length++;
    }
  return m_length;
}

void PromptUsername(char username[], int size)
{
  printf("Enter your username: ");
  fgets(username, size, stdin);

  size_t m_length = StringLength(username);
  if (m_length > 0 && username[m_length-1] == '\n')
  {
    username[m_length-1] = '\0';
  }
}

void PromptPassword(char password[])
{
  printf("Enter your password: ");
  scanf("%s", password);
}

void PrintBankMenu()
{
  printf("1. Deposit\n");
  printf("2. Withdraw\n");
  printf("3. Check Balance\n");
  printf("4. Exit\n");
}

void ProcessBankMenu(int choice)
{
  static int s_balance = 0;
  do
  {
    switch(choice)
    {
      case 1:
        Deposit(&s_balance);
        choice = GetBankChoice();
        break;
      case 2:
        Withdraw(&s_balance);
        choice = GetBankChoice(); 
        break;
      case 3:
        printf("Your balance is: %d\n", s_balance);
        choice = GetBankChoice(); 
        break;
      case 4:
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid choice. Please try again.\n");
        choice = GetBankChoice(); 
        break;
    }
  } while(choice != 4);
}

int StringCompare(const char str1[], const char str2[])
{
  size_t i = 0;
  while (str1[i] != '\0' && str2[i] != '\0')
  {
    if (str1[i] != str2[i])
    {
      return 0;
    }
    i++;
  }
  if (str1[i] == '\0' && str2[i] == '\0')
  {
    return 1;
  }
  return 0;
}

void CapitalizeWords(char str[])
{
    size_t i = 0;
    int m_inWord = 0; 
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!m_inWord && IsUpperLower(str[i]))
        {
            str[i] = UpperCase(str[i]);
            m_inWord = 1;
        }
        else if (ContainsSpace(str[i]))
        {
            m_inWord = 0;  
        }
    }
}

void DeCapitalizeWords(char str[])
{
  size_t i = 0;
  for (i = 0; str[i] != '\0'; i++)
  {
      if (IsUpperLower(str[i]))
      {
          str[i] = LowerCase(str[i]);
      }
  }
}

int IsUpperLower(const char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return 1;
    }
    return 0;
}

int UpperCase(const char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }
    return c;
}

int LowerCase(const char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + ('a' - 'A');
    }
    return c;
}

int ContainsSpace(const char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
    {
        return 1;
    }
    return 0;
}

void ValidateAndProcessLogin(UserInfo* userInfo)
{
    DeCapitalizeWords(userInfo->enteredUsername);
    if (StringCompare(userInfo->correctUsername, userInfo->enteredUsername) == 1 &&
        StringCompare(userInfo->correctPassword, userInfo->enteredPassword) == 1 &&
        IsInt(userInfo->enteredPassword) == 1)
    {
        CapitalizeWords(userInfo->enteredUsername);
        printf("Welcome %s\n", userInfo->enteredUsername);
        PrintBankMenu();
        scanf("%d", &(userInfo->choice));
        ProcessBankMenu(userInfo->choice);
    }
    else
    {
        printf("Wrong password or username!\n");
    }
}

void Deposit(int* balance)
{
    int amount;
    printf("Curent balance: %d\n", *balance);
    printf("Enter the amount to deposit: ");
    scanf("%d", &amount);
    *balance += amount;
    printf("Deposit successful.\nNew balance: %d\n", *balance);
}

void Withdraw(int* balance)
{
    int amount;
    printf("Curent balance: %d\n", *balance);
    printf("Enter the amount to withdraw: ");
    scanf("%d", &amount);
    if (amount > *balance)
    {
        printf("Insufficient balance.\n");
    }
    else
    {
        *balance -= amount;
        printf("Withdrawal successful.\nNew balance: %d\n", *balance);
    }
}

int GetBankChoice()
{
  int choice;
  PrintBankMenu();
  printf("Enter your next choice: ");
  scanf("%d", &choice);
  return choice;
}
