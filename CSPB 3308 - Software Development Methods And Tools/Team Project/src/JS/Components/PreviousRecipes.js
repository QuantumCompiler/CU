import React, { useState, useEffect } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import { AppBar, Box, IconButton, Toolbar, Typography, Drawer, List, ListItem, ListItemText, Grid } from '@mui/material';
import MenuIcon from '@mui/icons-material/Menu';
import LogoutIcon from '@mui/icons-material/Logout';
import PreviousCards from './PreviousCards';
import axios from 'axios';
import RecipeCards from './RecipeCards';

export default function PreviousRecipes() {
    const location = useLocation();
    const username = location.state?.username || 'Guest';
    const [drawerOpen, setDrawerOpen] = useState(false);
    const [searches, setSearches] = useState([]);
    const [selectedRecipe, setSelectedRecipe] = useState('');
    const [showRecipe, setShowRecipe] = useState(false);
    const navigate = useNavigate();

    useEffect(() => {
        const fetchSearches = async () => {
            const [isNotEmpty, userRecipes] = await grabRecipes(username);
            if (isNotEmpty) {
                setSearches(userRecipes);
            }
        };
        fetchSearches();
    }, [username]);

    const Logout = () => {
        navigate('/', { replace: true });
    };

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
                <ListItem onClick={() => navigate('/about', { state: { username } })} sx={{ cursor: 'pointer', textAlign: 'center' }}>
                    <ListItemText primary="About" />
                </ListItem>
                <ListItem onClick={() => navigate('/create-recipe', { state: { username } })} sx={{ cursor: 'pointer', textAlign: 'center' }}>
                    <ListItemText primary="Create New Recipe" />
                </ListItem>
                <ListItem onClick={() => navigate('/dashboard', { state: { username } })} sx={{ cursor: 'pointer', textAlign: 'center' }}>
                    <ListItemText primary="Dashboard" />
                </ListItem>
                <ListItem onClick={() => navigate('/settings', { state: { username } })} sx={{ cursor: 'pointer', textAlign: 'center' }}>
                    <ListItemText primary="Settings" />
                </ListItem>
            </List>
        </Box>
    );

    const handleRecipeClick = (recipe) => {
        if (showRecipe) {
            setShowRecipe(false);
            setTimeout(() => {
                localStorage.setItem('NewRecipe', recipe.result);
                setSelectedRecipe(recipe.result);
                setShowRecipe(true);
            }, 1);
        } else {
            localStorage.setItem('NewRecipe', recipe.result);
            setSelectedRecipe(recipe.result);
            setShowRecipe(true);
        }
    };

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
                    <Box sx={{ width: '40px' }} />
                    <Box sx={{ flexGrow: 1, textAlign: 'center', display: 'flex', justifyContent: 'center' }}>
                        <Typography variant="h6" component="div">
                            Previous Recipes
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
                            onClick={Logout}
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
            <Box height={'20px'} />
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
                <PreviousCards userName={username} searches={searches} onRecipeClick={handleRecipeClick} />
                {showRecipe && <RecipeCards recipe={selectedRecipe} />}
            </Grid>
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