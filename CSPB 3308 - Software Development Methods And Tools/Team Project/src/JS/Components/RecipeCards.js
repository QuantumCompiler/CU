import React from 'react';
import { Card, CardMedia, CardContent, CardActions, Typography} from '@mui/material';
import Recipe from '../Utilities/RecipeClass.js';

/*  RecipeCards - A class component to display recipe cards
    Inputs:
        None
    Algorithm:
        * Retrieve the most recent recipe data from local storage
        * Call the convertAPIResults function to convert the data to Recipe objects
        * Render a card for each Recipe object
    Return:
        A list of cards containing the recipe information
*/
export default class RecipeCards extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            recipes: []
        };
    }
    /*  convertAPIResults - A function to convert the results from the spoonacular API to Recipe objects
        Inputs:
            None
        Algorithm:
            * Retrieve the recipe data from local storage
            * Convert the data to JSON
            * Create an array of Recipe objects from the JSON data
        Return:
            An array of Recipe objects
    */
    convertAPIResults() {
        // Retrieve Recipe
        const stored = localStorage.getItem('NewRecipe');
        // Convert To JSON
        const storedJSON = JSON.parse(stored);
        // Create Recipes Array And Append
        const recipes = [];
        for (let i = 0; i < storedJSON.length; i++) {
            recipes.push(new Recipe(storedJSON[i]));
        }
        return recipes;
    }

    /*  componentDidMount - A lifecycle method that runs after the component has mounted
        Inputs:
            None
        Algorithm:
            * Set the state of the component to contain the converted API results
        Return:
            Updates the state of the component with the converted API results
    */
    componentDidMount() {
        this.setState({
            recipes: this.convertAPIResults()
        });
    }

    /*  render - A function to render the component
        Inputs:
            None
        Algorithm:
            * Map over the recipes array and render a card for each Recipe object
        Return:
            A list of cards containing the recipe information
    */
    render() {
        return (
            <div>
                {this.state.recipes.map((recipe, index) => (
                    <Card key={index} 
                        sx={{ 
                            margin: 2,
                            width: `${window.innerWidth / 2}px`,
                        }}
                    >
                        {/* Title Of Recipe */}
                        <CardContent>
                            <Typography
                                gutterBottom variant="h5" 
                                component="div"
                                align='center'
                            >
                                {recipe.Title} - {recipe.Likes} Likes
                            </Typography>
                        </CardContent>
                        {/* Image Of Recipe */}
                        <div
                            style={{display: 'flex', justifyContent: 'center', alignItems: 'center'}}
                        >
                            <CardMedia
                                component="img"
                                style={{height: '200px', width: '500px', objectFit: 'contain'}}
                                image={recipe.Image}
                                alt={recipe.Title}
                            />
                        </div>
                        {/* Content Of Recipe */}
                        <CardContent>
                            {/* Used Ingredients (Ingredients You Already Have) */}
                            <Typography
                                gutterBottom variant='p'
                                component="div"
                            >
                                Ingredients You Already Have: {recipe.UsedIngredientCount} - {' '}
                                <span style={{ color: 'blue'}}>
                                    {recipe.ShowUsedIngredientsNames()}
                                </span>
                            </Typography>
                            {/* Missing Ingredients (Ingredients You Are Missing) */}
                            <Typography
                                gutterBottom variant='p'
                                component='div'
                            >
                                Ingredients You Are Missing: {recipe.MissedIngredientCount} - {' '}
                                <span style={{ color: 'red'}}>
                                    {recipe.ShowMissingIngredientsNames()}
                                </span>
                            </Typography>
                        </CardContent>
                    </Card>
                ))}
            </div>
        );
    }
}