#include <stdio.h>
#include <string.h>

void printWeatherData(int year, int month, int day);
void printWeatherDescription(int year, int month, int day);

int main() {
  int choice;
  int year, month, day;    
  
  printf("\033[38;5;68m");

  printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
  printf("█             _                 _           █\n");
  printf("             | |               | |           \n");
  printf("         ___ | | ___  _   _  __| |___        \n");
  printf("        / __|| |/ _ \\| | | |/ _` / __|      \n");
  printf("       | (__ | | (_) | |_| | (_| \\__ \\     \n");
  printf("        \\___||_|\\___/ \\__,_|\\__,_|___/   \n");
  printf("█                                           █\n");
  printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");

  printf("\n\n");
  printf("☁ ☁ ☁ ☁ ☁ ☁ ☁ ☁ ☁ \n");
  printf("Welcome to 𝐂𝐋𝐎𝐔𝐃𝐒! The system about forecasts and temperature\n");
  printf("☁ ☁ ☁ ☁ ☁ ☁ ☁ ☁ ☁ \n");

  do
  {

    printf("\n\n Choose your option!\n");
    printf("\n1. View Weather Data\n");
    printf("2. View Weather Description\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
      case 1:
        printf("\n\nPlease enter year, month and day respectively to view the data:\n");
        scanf("%d %d %d", &year, &month, &day);
        printWeatherData(year, month, day);
        break;

      case 2:
        printf(
            "\n\nPlease enter year, month and day respectively to view the data:\n");
        scanf("%d %d %d", &year, &month, &day);
        printWeatherDescription(year, month, day);
        break;

      case 3:
        printf("Exiting program. Goodbye!\n");
        break;

      default:
        printf("Invalid choice. Please enter a valid option.\n");
    }

  } while (choice != 3);

  return 0;
}
void printWeatherData(int year, int month, int day)
{
  FILE* file;
  char line[200];
  char date[20];

  file = fopen("weather_data.txt", "r");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo de dados meteorológicos.\n");
    return;
  }

  printf("\nForecast for the date %d-%02d-%02d:\n", year, month, day);

  // Imprime o cabeçalho da tabela
  printf("\n");
  printf("| Date                | Temperature | Humidity | Pressure |\n");
  printf("|---------------------|-------------|----------|----------|\n");

  // le as linhas e formata
  while (fgets(line, sizeof(line), file) != NULL)
  {
    if (sscanf(line, "Data %19s;Temperatura:%*f;Humidade:%*d;Pressao:%*d", date) == 1)
    {
      int line_year, line_month, line_day;
      if (sscanf(date, "%04d-%02d-%02d", &line_year, &line_month, &line_day) ==
          3) {
        if (line_year == year && line_month == month && line_day == day) {
          char print_date[11], print_hour[9];
          float temperature;
          int humidity, pressure;

          // extrai os valores de temperatura umidade e pressao da linha
          sscanf(line, "Data %10s %8s;Temperatura:%f;Humidade:%d;Pressao:%d",
                 print_date, print_hour, &temperature, &humidity, &pressure);

          // imprime os valores formatados em uma linha de tabela
          printf("| %s %s | %-11.2f | %-8d |  %-7d |\n", print_date, print_hour,
                 temperature, humidity, pressure);
        }
      }
    }
  }
  fclose(file);
}

void printWeatherDescription(int year, int month, int day)
{
  FILE* file;
  char line[200];
  char date[20];

  file = fopen("weather_description.txt", "r");

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de dados meteorológicos.\n");
    return;
  }

  // Imprime o cabeçalho da tabela
  printf("\n");
  printf("| Date                | Weather          |\n");
  printf("|---------------------|------------------|\n");

  // le as linhas e formata
  while (fgets(line, sizeof(line), file) != NULL)
  {
    if (sscanf(line, "Data %19s %*s;Weather:%[^;]", date, line) == 2)
    {
      int line_year, line_month, line_day;
      if (sscanf(date, "%04d-%02d-%02d", &line_year, &line_month, &line_day) == 3)
      {
        if (line_year == year && line_month == month && line_day == day)
        {
          char print_date[11], print_hour[9];
          char weather[21];
          // extrai os valores de temperatura umidade e pressao da linha
          sscanf(line, "Data %10s %8s;Weather:%[^;]", print_date, print_hour,
                 weather);

          // imprime os valores formatados em uma linha de tabela
          printf("| %s %s | %s \n", print_date, print_hour, weather);
        }
      }
    }
  }

  fclose(file);
}
