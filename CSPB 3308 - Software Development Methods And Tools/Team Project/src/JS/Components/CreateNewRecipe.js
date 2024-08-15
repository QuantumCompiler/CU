import { Box, Button, Grid, Typography, FormControl, TextField, IconButton } from '@mui/material';
import React, { useState, useEffect, useCallback } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import DeleteIcon from '@mui/icons-material/Delete';
import AddCircle from '@mui/icons-material/AddCircle';
import SpoonAPI from '../Utilities/SpoonAPI.js';
import RecipeCards from './RecipeCards.js';
import AppBar from '@mui/material/AppBar';
import Toolbar from '@mui/material/Toolbar';
import MenuIcon from '@mui/icons-material/Menu';
import Drawer from '@mui/material/Drawer';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemText from '@mui/material/ListItemText';
import LogoutIcon from '@mui/icons-material/Logout';

export default function CreateRecipe() {
    const location = useLocation();
    const username = location.state?.username || 'Guest';
    const navigate = useNavigate();
    const [inputs, setInputs] = useState([{ value: '' }]);
    const [focusedIndex, setFocusedIndex] = useState(null);
    const [deleteIndex, setDeleteIndex] = useState(null);
    const [drawerOpen, setDrawerOpen] = useState(false);
    const [showCards, setShowCards] = useState(false);
    /*  AddInput - A function to add a new input to the inputs array
        Inputs:
            None
        Algorithm:
            * Add a new object to the inputs array with an empty value
        Return:
            Adds a new input to the inputs array
    */
    const AddInput = () => {
        setInputs([...inputs, { value: '' }]);
    }
    /*  DeleteInput - A function to delete an input from the inputs array
        Inputs:
            None
        Algorithm:
            * Filter the inputs array to remove the input at the specified index
        Dependencies:
            inputs: The current state of the inputs array
        Return:
            Updates the inputs array to remove the specified
    */
    const DeleteInput = useCallback((index) => {
        if (inputs.length > 1) {
            setInputs(currentInputs => currentInputs.filter((_, i) => i !== index));
        } else if (inputs.length === 1) {
            setInputs([{ value: '' }]);
        }
    }, [inputs, setInputs]);
    /*  DeleteAllInputs - A function to delete all inputs from the inputs array
        Inputs:
            None
        Algorithm:
            * Set the inputs array to an array with a single object containing an empty value
        Return:
            Updates the inputs array to contain a single input with an empty value
    */
    const DeleteAllInputs = () => {
        setInputs([{ value: ''}]);
        setShowCards(false);
    }
    /*  inputChange - A function to update the value of an input in the inputs array
        Inputs:
            index: The index of the input to be updated
            event: The event object containing the new value of the input
        Algorithm:
            * Map over the inputs array and update the value of the input at the specified index
        Return:
            Updates the value of the input at the specified index
    */
    const InputsChange = (index, event) => {
        var newInputs = inputs.map(function(input, i) {
            if (i === index) {
                return { value: event.target.value };
            }
            return input;
        });
        setInputs(newInputs);
    }
    const Logout = () => {
        navigate('/', {replace: true});
    }
    /*  Submit - A function to handle the form submission
        Inputs:
            event: The event object containing the form data
        Algorithm:
            * Prevent the default form submission behavior
            * Log the current state of the inputs array
        Return:
            Logs the current state of the inputs array
    */
    const Submit = async (event) => {
        localStorage.clear();
        event.preventDefault();
        var valid = true;
        for (let i = 0; i < inputs.length; i++) {
            if (inputs[i].value === '') {
                valid = false;
                break;
            }
        }
        if (valid === false) {
            alert('All ingredients must be entered, no blank entries allowed.');
        }
        else {
            var ingArray = [];
            for (let i = 0; i < inputs.length; i++) {
                ingArray.push(inputs[i]);
            }
            ingArray.sort((a, b) => {
                return a.value.localeCompare(b.value);
            });
            await SpoonAPI(ingArray, {username}, 10, 1, true);
            ToggleCards();
        }
    }
    /*  ToggleCards - A function to toggle the visibility of the recipe cards
        Inputs:
            None
        Algorithm:
            * Update the showCards state to the opposite of its current value
        Return:
            Toggles the visibility of the recipe cards
    */
    const ToggleCards = () => {
        setShowCards(!showCards);
    }
    useEffect(() => {
        if (deleteIndex !== null) {
            DeleteInput(deleteIndex);
            setDeleteIndex(null);
        }
    }, [deleteIndex, DeleteInput]);
    const ToggleDrawer = (open) => (event) => {
        if (event.type === 'keydown' && (event.key === 'Tab' || event.key === 'Shift')) {
            return;
        }
        setDrawerOpen(open);
    };
    const list = () => (
        <Box
            sx={{ width: 250 }}
            role="presentation"
            onClick={ToggleDrawer(false)}
            onKeyDown={ToggleDrawer(false)}
        >
            <List>
                <ListItem onClick={() => navigate('/about', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="About" />
                </ListItem>
                <ListItem onClick={() => navigate('/dashboard', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="Dashboard" />
                </ListItem>
                <ListItem onClick={() => navigate('/previous-recipes', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="Previous Recipes" />
                </ListItem>
                <ListItem onClick={() => navigate('/settings', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="Settings" />
                </ListItem>
            </List>
        </Box>
    );
    return (
        <Box sx={{ flexGrow: 1 }}>
            <AppBar position="static">
                <Toolbar sx={{ backgroundColor: '#272727', display: 'flex', justifyContent: 'space-between' }}>
                    <Box sx={{ display: 'flex', alignItems: 'center' }}>
                        <IconButton
                            size="large"
                            edge="start"
                            color="inherit"
                            aria-label="menu"
                            sx={{ mr: 2 }}
                            onClick={ToggleDrawer(true)}
                        >
                            <MenuIcon />
                        </IconButton>
                    </Box>
                    <Box sx={{ width: '40px' }}/>
                    <Box sx={{ flexGrow: 1, textAlign: 'center', display: 'flex', justifyContent: 'center' }}>
                        <Typography variant="h6" component="div">
                            Create New Recipe
                        </Typography>
                    </Box>
                    <Box sx={{ display: 'flex', alignItems: 'center' }}>
                        <Typography variant="body1" component="div" sx={{ ml: 'auto' }}>
                            {username}
                        </Typography>
                        <IconButton 
                            size="small"
                            edge="end"
                            color="inherit"
                            aria-label="logout"
                            sx={{ ml: 2 }}
                            onClick={() => Logout()}
                        >
                            <LogoutIcon />
                        </IconButton>
                    </Box>
                </Toolbar>
            </AppBar>
            <Drawer
                anchor="left"
                open={drawerOpen}
                onClose={ToggleDrawer(false)}
            >
                {list()}
            </Drawer>
            <Box height={'10px'}/>
            <Grid
                sx={{
                    display: 'flex',
                    flexDirection: 'column',
                    justifyContent: 'center',
                    backgroundColor: '#f0f0f0',
                    alignItems: 'center',
                    pt: 3,
                    pb: 5,
                }}
            >
                <Box
                    component="form"
                    onSubmit={Submit}
                    sx={{
                        width: `${window.innerWidth / 2}px`,
                        bgcolor: 'white',
                        p: 3,
                        borderRadius: 1,
                        boxShadow: 3,
                    }}
                >
                    <Typography variant="h5" component="h1" gutterBottom textAlign="center">
                        Enter Ingredients
                    </Typography>
                    {inputs.map((input, index) => (
                        <Box key={index} sx={{ display: 'flex', alignItems: 'center', marginBottom: 2 }}>
                            <FormControl fullWidth>
                                <TextField
                                    label={`Ingredient ${index + 1}`}
                                    value={input.value}
                                    onChange={(event) => InputsChange(index, event)}
                                    variant="outlined"
                                    fullWidth
                                    onFocus={() => setFocusedIndex(index)}
                                    onBlur={() => setFocusedIndex(null)}
                                />
                            </FormControl>
                            {focusedIndex === index && (
                                <IconButton
                                    color="secondary"
                                    aria-label="delete"
                                    onMouseDown={() => setDeleteIndex(index)}
                                    sx={{ marginLeft: 2 }}
                                >
                                    <DeleteIcon />
                                </IconButton>
                            )}
                        </Box>
                    ))}
                    <Box
                        sx={{
                            display: 'flex',
                            justifyContent: 'center',
                            mt: 2,
                        }}
                    >
                        <IconButton 
                            color="secondary" 
                            aria-label='add'
                            onClick={AddInput}
                        >
                            <AddCircle/>
                        </IconButton>
                    </Box>
                    <Box
                        sx={{
                            display: 'flex',
                            justifyContent: 'center',
                            gap: 2,
                            mt: 2,
                        }}
                    >
                        <Button
                            color='primary'
                            variant='contained'
                            onClick={Submit}
                        >
                            Create Recipe
                        </Button>
                        <Button
                            color='secondary'
                            variant='contained'
                            onClick={DeleteAllInputs}
                        >
                            Clear
                        </Button>
                    </Box>
                </Box>
                {showCards && <RecipeCards />}
            </Grid>
        </Box>
    );
}