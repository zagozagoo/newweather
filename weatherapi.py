import requests, json

api_key = "61f671689e4cb0c68eafe8a163c7ebdd"

city_name = input("Enter city name : ")

# Link da API que pega as coordenadas geográficas do local especificado (Documentação: https://openweathermap.org/api/geocoding-api)
geocoding = "http://api.openweathermap.org/geo/1.0/direct?q=" + city_name + "&limit=1&appid=" + api_key
georesponse = requests.get(geocoding) # Manda uma requisição para a API
geojson = georesponse.json()[0] # Salva a resposta da API como json em uma variável

# Link que pega a previsão do tempo do local especificado
base_url = "https://api.openweathermap.org/data/2.5/forecast?lat="

# Concatena todas as informações em um link(as informações do json estão sendo convertidas 
# para string para poderem ser concatenadas)
histweather = base_url + str(geojson["lat"]) + "&lon=" + str(geojson["lon"]) + "&appid=" + api_key + "&units=metric"
histresponse = requests.get(histweather)
histjson = histresponse.json()

with open ("weather_data.txt", "w") as file:

# Percorre a lista dentro do json que possui todas as informações de previsão dos proximos 5 dias
    for i in range(len(histjson["list"])): # :)
        list_data = histjson["list"][i] # Valor atual da lista
        main_info = list_data["main"] # Pegando os dados principais do valor atual

        # Salvando as informações principais do valor atual da lista em uma vari

        file.write(f"Data {list_data['dt_txt']};") # Printando a data exata daquelas informações
        file.write(f"Temperatura:{main_info['temp']};")
        file.write(f"Humidade:{main_info['humidity']};")
        file.write(f"Pressao:{main_info['pressure']}\n")

with open ("weather_description.txt", "w") as file:

# Percorre a lista dentro do json que possui todas as informações de previsão dos proximos 5 dias
    for i in range(len(histjson["list"])): 
        list_data = histjson["list"][i]
        weather_info = list_data["weather"]

        for j in range(len(weather_info)):
            file.write(f"Data {list_data['dt_txt']};")
            file.write(f"Weather:{weather_info[j]['description']};")
            file.write(f"{weather_info[j]['icon']}\n")

print("Dados metereologicos foram salvos nos arquivo 'weather_data.txt' e 'weather_description.txt'")
