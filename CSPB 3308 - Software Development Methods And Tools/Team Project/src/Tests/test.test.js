import '@testing-library/jest-dom';
import React from 'react';
import { render, screen } from '@testing-library/react';
import { BrowserRouter } from 'react-router-dom';
import CreateRecipe from '../JS/Components/CreateNewRecipe';
import Dashboard from '../JS/Components/Dashboard';
import Login from '../JS/Components/Login';
import Register from '../JS/Components/Register';

test('Renders Login', () => {
    render(
        <BrowserRouter>
            <Login />
        </BrowserRouter>
    );
});

test('Renders Register', () => {
    render(
        <BrowserRouter>
            <Register />
        </BrowserRouter>
    );
});

test('Renders Dashboard', () => {
    render(
        <BrowserRouter>
            <Dashboard />
        </BrowserRouter>
    );
});

test('Renders Create New Recipe', () => {
    render(
        <BrowserRouter>
            <CreateRecipe />
        </BrowserRouter>
    )
});