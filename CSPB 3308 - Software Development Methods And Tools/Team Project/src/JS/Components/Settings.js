import React, { useState } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';
import { AppBar, Box, Button, Grid, IconButton, Toolbar, Typography } from '@mui/material';
import MenuIcon from '@mui/icons-material/Menu';
import Drawer from '@mui/material/Drawer';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemText from '@mui/material/ListItemText';
import LogoutIcon from '@mui/icons-material/Logout';
import axios from 'axios';

export default function Settings() {
    const location = useLocation();
    const username = location.state?.username || 'Guest';
    const [drawerOpen, setDrawerOpen] = useState(false);
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
                <ListItem onClick={() => navigate('/dashboard', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="Dashboard"/>
                </ListItem>
                <ListItem onClick={() => navigate('/previous-recipes', {state: {username}})} sx={{cursor: 'pointer', textAlign: 'center'}}>
                    <ListItemText primary="Previous Recipes"/>
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
                            onClick={toggleDrawer(true)}
                        >
                            <MenuIcon />
                        </IconButton>
                    </Box>
                    <Box sx={{ width: '40px' }}/>
                    <Box sx={{ flexGrow: 1, textAlign: 'center', display: 'flex', justifyContent: 'center' }}>
                        <Typography variant="h6" component="div">
                            Settings
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
                    sx={{
                        width: `${window.innerWidth / 2}px`,
                        bgcolor: 'white',
                        p: 3,
                        borderRadius: 1,
                        boxShadow: 3,
                        textAlign: 'center',
                    }}
                >
                    <Typography>
                        User History
                    </Typography>
                    <Box height={'20px'}/>
                    <Button
                        color='primary'
                        variant='contained'
                        onClick={() => deleteDBEntries(username)}
                    >
                        Clear Recipes
                    </Button>
                </Box>
            </Grid>
        </Box>
    );
}

async function deleteAllRecipes(userName) {
    let result = false;
    let response = '';
    try {
        const response = await axios.post('http://localhost:3308/delete-all-recipes', {
            user_id: userName,
        });
        if (response.status === 200) {
            const { success, message } = response.data;
            result = success;
            response = message;
            return [result, response];
        }
    } catch (error) {
        console.error(`Error occurred: ${error.message}`);
    }
    return [result, response];
}

async function deleteDBEntries(userName) {
    var data = await grabRecipes(userName);
    if (data[0] === true) {
        let text = `Are you sure that you want to delete all recipes that you have created?\n\nYou currently have ${data[1].length} recipe entries.`;
        if (window.confirm(text) === true) {
            await deleteAllRecipes(userName);
        } else {
            console.log('Selected false');
        }
    } else {
        return;
    }
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