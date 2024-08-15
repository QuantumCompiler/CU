#!/usr/bin/python3

import os
import json
import urllib.request

# Define the path to the SVG file
svg_file_path = os.path.join(os.path.dirname(__file__), '..', 'images', 'Blank_US_Map.svg')

# Ensure the SVG file exists
if not os.path.isfile(svg_file_path):
    print("Content-type: text/html")
    print()  # This extra newline is important!
    print("<html><body><h1>Error: SVG file not found</h1></body></html>")
    exit(1)

# Function to get weather data
def get_weather_data(lat, lon):
    url = f'https://api.weather.gov/points/{lat},{lon}'
    with urllib.request.urlopen(url) as response:
        data = json.loads(response.read().decode())
        grid_id = data['properties']['gridId']
        grid_x = data['properties']['gridX']
        grid_y = data['properties']['gridY']
        forecast_url = f'https://api.weather.gov/gridpoints/{grid_id}/{grid_x},{grid_y}/forecast'
        with urllib.request.urlopen(forecast_url) as response:
            forecast_data = json.loads(response.read().decode())
            temperature = forecast_data['properties']['periods'][0]['temperature']
            return temperature

# Function to get color based on temperature
def get_color(temp):
    if temp <= -11:
        return 'Navy'
    elif temp <= -1:
        return 'Blue'
    elif temp <= 9:
        return 'DodgerBlue'
    elif temp <= 19:
        return 'LightSkyBlue'
    elif temp <= 29:
        return 'LightBlue'
    elif temp <= 39:
        return 'MediumAquamarine'
    elif temp <= 49:
        return 'Aquamarine'
    elif temp <= 59:
        return 'PaleGreen'
    elif temp <= 69:
        return 'Khaki'
    elif temp <= 79:
        return 'Gold'
    elif temp <= 89:
        return 'Orange'
    elif temp <= 99:
        return 'Tomato'
    elif temp <= 109:
        return 'Red'
    else:
        return 'DarkRed'

# Mapping of state abbreviations to coordinates
state_coords = {
    "ak": (61.3850, -152.2683),
    "al": (32.7990, -86.8073),
    "ar": (34.9513, -92.3809),
    "az": (33.7712, -111.3877),
    "ca": (36.1700, -119.7462),
    "co": (39.0646, -105.3272),
    "ct": (41.5834, -72.7622),
    "de": (39.3498, -75.5148),
    "fl": (27.8333, -81.7170),
    "ga": (32.9866, -83.6487),
    "hi": (21.1098, -157.5311),
    "ia": (42.0046, -93.2140),
    "id": (44.2394, -114.5103),
    "il": (40.3363, -89.0022),
    "in": (39.8647, -86.2604),
    "ks": (38.5111, -96.8005),
    "ky": (37.6690, -84.6514),
    "la": (31.1801, -91.8749),
    "ma": (42.2373, -71.5314),
    "md": (39.0724, -76.7902),
    "me": (44.6074, -69.3977),
    "mi": (43.3504, -84.5603),
    "mn": (45.7326, -93.9196),
    "mo": (38.4623, -92.3020),
    "ms": (32.7673, -89.6812),
    "mt": (46.9048, -110.3261),
    "nc": (35.6411, -79.8431),
    "nd": (47.5362, -99.7930),
    "ne": (41.1289, -98.2883),
    "nh": (43.4108, -71.5653),
    "nj": (40.3140, -74.5089),
    "nm": (34.8375, -106.2371),
    "nv": (38.4199, -117.1219),
    "ny": (42.1497, -74.9384),
    "oh": (40.3736, -82.7755),
    "ok": (35.5376, -96.9247),
    "or": (44.5672, -122.1269),
    "pa": (40.5773, -77.2640),
    "ri": (41.6772, -71.5101),
    "sc": (33.8191, -80.9066),
    "sd": (44.2853, -99.4632),
    "tn": (35.7449, -86.7489),
    "tx": (31.1060, -97.6475),
    "ut": (40.1135, -111.8535),
    "va": (37.7680, -78.2057),
    "vt": (44.0407, -72.7093),
    "wa": (47.3917, -121.5708),
    "wi": (44.2563, -89.6385),
    "wv": (38.4680, -80.9696),
    "wy": (42.7475, -107.2085)
}

# Print the content-type header
print("Content-type: text/html")
print()  # This extra newline is important!

# Print the HTML header and include the JavaScript code in the <head>
print('''<!DOCTYPE html>
<html>
<head>
    <title>US Map Lab by Your Last Name</title>
    <link rel="icon" href="data:,">
    <script>
        async function fetchWeather(lat, lon, state) {
            const response = await fetch(`https://api.weather.gov/points/${lat},${lon}`);
            const data = await response.json();
            const gridId = data.properties.gridId;
            const gridX = data.properties.gridX;
            const gridY = data.properties.gridY;
            const forecastResponse = await fetch(`https://api.weather.gov/gridpoints/${gridId}/${gridX},${gridY}/forecast`);
            const forecastData = await forecastResponse.json();
            const temperature = forecastData.properties.periods[0].temperature;
            const color = getColor(temperature);
            const elements = document.getElementsByClassName(state);
            for (let i = 0; i < elements.length; i++) {
                elements[i].setAttribute('fill', color);
            }
        }

        function getColor(temp) {
            if (temp <= -11) {
                return 'Navy';
            } else if (temp <= -1) {
                return 'Blue';
            } else if (temp <= 9) {
                return 'DodgerBlue';
            } else if (temp <= 19) {
                return 'LightSkyBlue';
            } else if (temp <= 29) {
                return 'LightBlue';
            } else if (temp <= 39) {
                return 'MediumAquamarine';
            } else if (temp <= 49) {
                return 'Aquamarine';
            } else if (temp <= 59) {
                return 'PaleGreen';
            } else if (temp <= 69) {
                return 'Khaki';
            } else if (temp <= 79) {
                return 'Gold';
            } else if (temp <= 89) {
                return 'Orange';
            } else if (temp <= 99) {
                return 'Tomato';
            } else if (temp <= 109) {
                return 'Red';
            } else {
                return 'DarkRed';
            }
        }

        window.onload = function() {''')

# Generate JavaScript to call fetchWeather for each state
for state, (lat, lon) in state_coords.items():
    print(f'fetchWeather({lat}, {lon}, "{state}");')

# Close the JavaScript and HTML head
print('''
        };
    </script>
</head>
<body>
''')

# Read and print the SVG file contents
with open(svg_file_path, 'r') as svg_file:
    for line in svg_file:
        print(line, end='')

# Print the closing tags for body and html
print('''
</body>
</html>
''')