import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import About from './Components/About.js';
import CreateRecipe from './Components/CreateNewRecipe';
import Dashboard from './Components/Dashboard';
import Login from './Components/LogIn.js';
import Register from './Components/Register';
import Settings from './Components/Settings.js';
import Previous from './Components/PreviousRecipes.js';

export default function App() {
  return (
    <Router>
      <div className='App'>
        <Routes>
          <Route path='/' element={<Login />}/>
          <Route path='/about' element={<About />}/>
          <Route path='/create-recipe' element={<CreateRecipe />}/>
          <Route path='/dashboard' element={<Dashboard />}/>
          <Route path='/previous-recipes' element={<Previous />}/>
          <Route path='/register' element={<Register />}/>
          <Route path='/settings' element={<Settings />}/>
        </Routes>
      </div>
    </Router>
  );
}