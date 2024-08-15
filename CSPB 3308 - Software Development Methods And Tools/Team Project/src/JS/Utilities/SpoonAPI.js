import axios from 'axios';
/*  SpoonAPI - A function to get recipes by ingredients with spoonacular API
    Inputs:
        ingredients: A string of ingredients separated by commas
        number: The number of recipes to return (default: 10)
        ranking: The ranking of the recipes (default: 1)
        ignorePantry: A boolean to ignore pantry ingredients (default: false)
    Algorithm:
        * Create a query object with the specified parameters
            * ingredients: The list of ingredients
            * number: The number of recipes to return
            * ranking: The ranking of the recipes
            * ignorePantry: A boolean to ignore pantry ingredients
        * Create a URL object with the spoonacular API endpoint
        * Add the query parameters to the URL
        * Create a headers object with the API key and host
            * x-rapidapi-key - 0969f52154mshf5d39e0b2d8cbf0p1af05bjsn7ac99719ef08
            * x-rapidapi-host - spoonacular-recipe-food-nutrition-v1.p.rapidapi.com
        * Fetch the data from the API using the URL and headers
            * Response is converted to JSON
            * Data is stored in local storage
            * Data is logged to the console
            * Error is logged to the console (if applicable)
    Return:
        Logs the data from the spoonacular API to the console
*/
export default async function SpoonAPI(ingArray, username, number = 10, ranking = 1, ignorePantry = false) {
    var newRecipe = false;
    console.clear();
    const userName = username.username;
    let ingredients = ingArray.map(ing => ing.value).join(',');
    const [recipeExists, previousRecipe] = await searchDB(userName, ingredients);
    if (recipeExists) {
        console.log(`Recipe with ingredients {${ingredients}} already exists! Spoonacular call subverted.`);
        localStorage.setItem('NewRecipe', previousRecipe.result);
        console.log('Recipe added to local storage as NewRecipe');
    } else {
        console.log(`Recipe with ingredients {${ingredients}} was not found`);
        const query = {
            ingredients: ingredients,
            number: number,
            ranking: ranking,
            ignorePantry: ignorePantry
        };
        const url = new URL("https://spoonacular-recipe-food-nutrition-v1.p.rapidapi.com/recipes/findByIngredients");
        url.search = new URLSearchParams(query).toString();
        const headers = {
            "x-rapidapi-key": "0969f52154mshf5d39e0b2d8cbf0p1af05bjsn7ac99719ef08",
            "x-rapidapi-host": "spoonacular-recipe-food-nutrition-v1.p.rapidapi.com"
        };
        try {
            console.log('Sending request to spoonacular.');
            const response = await fetch(url, { headers: headers });
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const data = await response.json();
            const stringData = JSON.stringify(data);
            localStorage.setItem('NewRecipe', stringData);
            console.log('Response received from spoonacular.');
            await addRecipe(userName, ingredients, stringData);
            newRecipe = true;
        } catch (error) {
            console.error('Error:', error);
        }
    }
    return newRecipe;
}

async function searchDB(userName, ingredients) {
    let recipeExists = false;
    let previousRecipe = '';
    try {
        const response = await axios.post('http://localhost:3308/search-recipe', {
            user_id: userName,
            ingredients: ingredients
        });
        if (response.status === 200) {
            const { exists, recipe } = response.data;
            recipeExists = exists;
            previousRecipe = recipe;
            return [recipeExists, previousRecipe];
        }
    } catch (error) {
        console.error(`Error occurred: ${error.message}`);
    }
    return [recipeExists, previousRecipe];
}

async function addRecipe(user_id, ingredients, result) {
    try {
        const response = await axios.post('http://localhost:3308/add-recipe', {
            user_id,
            ingredients,
            result
        });
        if (response.status === 200 || response.status === 201) {
            const data = response.data;
            console.log(`Recipe added successfully with ID: ${data.id}`);
        } else {
            const errorData = response.data;
            console.error(`Error occurred: ${errorData.error}`);
        }
    } catch (error) {
        console.error('Error config:', error.config);
    }
}