#include <stdio.h>
#include <string.h>

int main()
{
  FILE* file;
  char line[200];
  char date[20];
  int year, month, day;

  system("color 3E");

  file = fopen("weather_data.txt", "r");

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de dados meteorológicos.\n");
    return 1;
  }

  printf("█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n");
  printf("█             _                 _           █\n");
  printf("             | |               | |           \n");
  printf("         ___ | | ___  _   _  __| |___        \n");
  printf("        / __|| |/ _ \\| | | |/ _` / __|      \n");
  printf("       | (__ | | (_) | |_| | (_| \\__ \\     \n");
  printf("        \\___||_|\\___/ \\__,_|\\__,_|___/   \n");
  printf("█                                           █\n");
  printf("█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n");

  printf("\n\n");
  printf("☁ ☁ ☁ ☁ ☁ ☁ ☁ ☁ ☁ \n");
  printf("Welcome to 𝐂𝐋𝐎𝐔𝐃𝐒! The system about forecasts and temperature\n");
  printf("☁ ☁ ☁ ☁ ☁ ☁ ☁ ☁ ☁ \n");
  printf("\n\nPlease enter year, month and day respectively to view the data:\n");
  scanf("%d %d %d", &year, &month, &day);
  printf("\nForecast for the date %d-%02d-%02d:\n", year, month, day);

  // Imprime o cabeçalho da tabela
  printf("\n");
  printf("| Date                | Temperature | Humidity | Pressure |\n");
  printf("|---------------------|-------------|----------|----------|\n");

  // le as linhas e formata
  while (fgets(line, sizeof(line), file) != NULL)
  {
    if (sscanf(line, "%*s %10s", date) == 1)
    {
      int line_year, line_month, line_day;
      if (sscanf(date, "%04d-%02d-%02d", &line_year, &line_month, &line_day) == 3)
      {
        if (line_year == year && line_month == month && line_day == day)
        {
          char print_date[11], print_hour[9];
          float temperature;
          int humidity, pressure;

          // extrai os valores de temperatura umidade e pressao da linha
          sscanf(line, "Data %10s %8s;Temperatura:%f;Humidade:%d;Pressao:%d", print_date, print_hour, &temperature, &humidity, &pressure);

          // imprime os valores formatados em uma linha de tabela
          printf("| %s %s | %-11.2f | %-8d | %-7d |\n", print_date, print_hour, temperature, humidity, pressure);
        }
      }
    }
  }

  fclose(file);
  return 0;
}