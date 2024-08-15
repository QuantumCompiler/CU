import React, { useEffect, useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { Box, Card, CardContent, Typography, FormControl, TextField, Button } from '@mui/material';
import axios from 'axios';

export default function Register() {
    const [username, setUserName] = useState('');
    const [password, setPassword] = useState('');
    const [confirmPassword, setConfirmPassword] = useState('');
    const navigate = useNavigate();
    const handleRegister = async (e) => {
        e.preventDefault();
        if (username === "" || password === "" || confirmPassword === "") {
            console.log('Not all fields have been entered.');
            alert('All fields must be entered.');
            return;
        }
        if (password !== confirmPassword) {
            console.log('Passwords do not match.');
            alert('Passwords do not match.');
            return;
        }
        else if (password === confirmPassword) {
            console.log('Passwords match');
            try {
                const response = await axios.post('http://localhost:3308/users', {
                    username,
                    password
                });
                if (response.status === 201) {
                    navigate('/dashboard', {state: {username}, replace: true})
                } else {
                    alert('An unexpected error occurred.');
                }
            } catch (error) {
                alert(`An error occurred during registration.\n ${error} \nPlease try again.`);
            }

        } 
    }

    return (
        <div
            style={{
                display: 'flex',
                justifyContent: 'center',
                alignItems: 'center',
                height: '100vh',
                width: '100vw',
            }}
        >
            <Card
                sx={{
                    margin: 2,
                    width: 500,
                    padding: 3,
                }}
            >
                <CardContent>
                    <Typography
                        gutterBottom variant='h2'
                        component='div'
                        align='center'
                    >
                        Register
                    </Typography>
                    <Box
                        component="form"
                        onSubmit={handleRegister}
                        sx={{
                            display: 'flex',
                            flexDirection: 'column',
                            gap: 2,
                        }}
                    >
                        <FormControl fullWidth>
                            <TextField
                                id="username"
                                label="Username"
                                variant="outlined"
                                value={username}
                                onChange={(e) => setUserName(e.target.value)}
                            />
                        </FormControl>
                        <FormControl fullWidth>
                            <TextField
                                id="password"
                                label="Password"
                                type="password"
                                variant="outlined"
                                value={password}
                                onChange={(e) => setPassword(e.target.value)}
                            />
                        </FormControl>
                        <FormControl fullWidth>
                            <TextField
                                id="confirm-password"
                                label="Enter Password Again"
                                type="password"
                                variant="outlined"
                                value={confirmPassword}
                                onChange={(e) => setConfirmPassword(e.target.value)}
                            />
                        </FormControl>
                        <Button type='submit' variant='contained' color='primary'>
                            Register
                        </Button>
                        <Button component={Link} to='/' variant='contained' color='primary'>
                            Return To Login
                        </Button>
                    </Box>
                </CardContent>
            </Card>
        </div>
    );
}