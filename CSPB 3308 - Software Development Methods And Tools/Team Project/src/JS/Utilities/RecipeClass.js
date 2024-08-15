import Ingredient from './IngredientClass.js'
/*  Recipe - A class to store recipe information
    Inputs:
        recipeInfo: An object containing the recipe information
    Properties:
        ID: The ID of the recipe
        Title: The title of the recipe
        Image: The URL of the recipe image
        ImageType: The type of image
        UsedIngredientCount: The number of used ingredients
        MissedIngredientCount: The number of missing ingredients
        MissedIngredients: An array of missing ingredients
        UsedIngredients: An array of used ingredients
        UnusedIngredients: An array of unused ingredients
        Likes: The number of likes for the recipe
    Methods:
        ShowUsedIngredientsNames: A function to display the names of the used ingredients
        ShowMissingIngredientsNames: A function to display the names of the missing ingredients
*/
export default class Recipe {
    constructor(recipeInfo) {
        this.ID = recipeInfo.id;
        this.Title = recipeInfo.title;
        this.Image = recipeInfo.image;
        this.ImageType = recipeInfo.imageType;
        this.UsedIngredientCount = recipeInfo.usedIngredientCount;
        this.MissedIngredientCount = recipeInfo.missedIngredientCount;
        this.MissedIngredients = [];
        for (let i = 0; i < this.MissedIngredientCount; i++) {
            this.MissedIngredients.push(new Ingredient(recipeInfo.missedIngredients[i]));
        }
        this.UsedIngredients = [];
        for (let i = 0; i < this.UsedIngredientCount; i++) {
            this.UsedIngredients.push(new Ingredient(recipeInfo.usedIngredients[i]));
        }
        this.UnusedIngredients = [];
        for (let i = 0; i < this.UnusedIngredients.length; i++) {
            this.UnusedIngredients.push(new Ingredient(recipeInfo.unusedIngredients[i]));
        }
        this.Likes = recipeInfo.likes;
    }

    /*  ShowUsedIngredientsNames - A function to display the names of the used ingredients
        Inputs:
            None
        Algorithm:
            * Create a string to store the names of the used ingredients
            * Loop over the used ingredients and append the names to the string
            * Return the string
        Return:
            A string containing the names of the used ingredients
    */
    ShowUsedIngredientsNames() {
        var used = '';
        for (let i = 0; i < this.UsedIngredientCount; i++) {
            if (i < this.UsedIngredientCount - 1) {
                used += this.UsedIngredients[i].Name + ", ";
            }
            else {
                used += this.UsedIngredients[i].Name + ".";
            }
        }
        return used;
    }

    /*  ShowMissingIngredientsNames - A function to display the names of the missing ingredients
        Inputs:
            None
        Algorithm:
            * Create a string to store the names of the missing ingredients
            * Loop over the missed ingredients and append the names to the string
            * Return the string
        Return:
            A string containing the names of the missing ingredients
    */
    ShowMissingIngredientsNames() {
        var missing = '';
        for (let i = 0; i < this.MissedIngredientCount; i++) {
            if (i < this.MissedIngredientCount - 1) {
                missing += this.MissedIngredients[i].Name + ", ";
            }
            else {
                missing += this.MissedIngredients[i].Name + ".";
            }
        }
        return missing;
    }
}