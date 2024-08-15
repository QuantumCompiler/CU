import React, { useEffect, useState } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import IconButton from '@mui/material/IconButton';
import MenuIcon from '@mui/icons-material/Menu';
import Drawer from '@mui/material/Drawer';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemText from '@mui/material/ListItemText';
import LogoutIcon from '@mui/icons-material/Logout';
import axios from 'axios';
import RecipeCards from './RecipeCards.js';

export default function Dashboard() {
    const location = useLocation();
    const username = location.state?.username || 'Guest';
    const [drawerOpen, setDrawerOpen] = useState(false);
    const [isNotEmpty, setIsNotEmpty] = useState(false);
    const navigate = useNavigate();
    const Logout = () => {
        navigate('/', {replace: true});
    }
    const toggleDrawer = (open) => (event) => {
        if (event.type === 'keydown' && (event.key === 'Tab' || event.key === 'Shift')) {
            return;
        }
        setDrawerOpen(open);
    };
    const list = () => (
        <Box
            sx={{ width: 250 }}
            role="presentation"
            onClick={toggleDrawer(false)}
            onKeyDown={toggleDrawer(false)}
        >
            <List>
                <ListItem onClick={() => navigate('/about', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="About"/>
                </ListItem>
                <ListItem onClick={() => navigate('/create-recipe', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="Create New Recipe"/>
                </ListItem>
                <ListItem onClick={() => navigate('/previous-recipes', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="Previous Recipes"/>
                </ListItem>
                <ListItem onClick={() => navigate('/settings', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="Settings"/>
                </ListItem>
            </List>
        </Box>
    );
    useEffect(() => {
        const fetchRecipe = async () => {
            const [notEmpty] = await selectRecipe(username);
            setIsNotEmpty(notEmpty);
        };
        fetchRecipe();
    }, [username]);
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
                            onClick={toggleDrawer(true)}
                        >
                            <MenuIcon />
                        </IconButton>
                    </Box>
                    <Box sx={{ width: '40px' }}/>
                    <Box sx={{ flexGrow: 1, textAlign: 'center', display: 'flex', justifyContent: 'center' }}>
                        <Typography variant="h6" component="div">
                            Dashboard
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
                onClose={toggleDrawer(false)}
            >
                {list()}
            </Drawer>
            <Box height={'20px'}/>
            <Box
                sx={{
                    justifyContent: 'center',
                    textAlign: 'center'
                }}
            >
                {isNotEmpty ? 
                <Typography>
                    Hello, {username}. Welcome back. Previous recipe:<br/>
                </Typography> : 
                <Typography>
                    Hello, {username}. Navigate to Create New Recipe to create a new recipe. <br/>
                </Typography>}
                {isNotEmpty ? 
                    <Box
                        sx={{
                            display: 'flex',
                            justifyContent: 'center',
                        }}
                    >
                        <RecipeCards/>
                    </Box>
                : ""}
            </Box>
        </Box>
    );
}

async function grabRecipes(userName) {
    let isNotEmpty = false;
    let userRecipes = [];
    try {
        const response = await axios.post('http://localhost:3308/grab-all-recipes', {
            user_id: userName,
        });
        if (response.status === 200) {
            const { notEmpty, recipes } = response.data;
            isNotEmpty = notEmpty;
            userRecipes = recipes;
            return [isNotEmpty, userRecipes];
        }
    } catch (error) {
        console.error(`Error occurred: ${error.message}`);
    }
    return [isNotEmpty, userRecipes];
}

async function selectRecipe(userName) {
    let results = await grabRecipes(userName);
    if (results[0] === false) {
        return [false, []];
    } else {
        var numOfRecipes = results[1].length;
        var randomRecipeNum = getRandomInt(0, numOfRecipes);
        var randomRecipe = results[1][randomRecipeNum].result;
        if (localStorage.length > 0) {
            localStorage.clear();
        }
        localStorage.setItem('NewRecipe', randomRecipe);
        return [true, results[1]];
    }
}

function getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min)) + min;
}