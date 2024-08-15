import React from 'react';
import { Card, CardContent, Typography, Box, ListItemButton, ListItemText } from '@mui/material';
import { blue } from '@mui/material/colors';

export default class PreviousCards extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            userName: props.userName || "",
            searches: props.searches,
        };
    }

    componentDidUpdate(prevProps) {
        if (prevProps.searches !== this.props.searches) {
            this.setState({ searches: this.props.searches });
        }
    }

    render() {
        const { onRecipeClick } = this.props;
        return (
            <div>
                <Card 
                    sx={{ 
                        margin: 2,
                        width: `${window.innerWidth / 2}px`,
                    }}
                >
                    <CardContent>
                        <Typography
                            sx={{
                                textAlign: 'center'
                            }}
                        >
                            Hello {this.state.userName}, you have created {this.state.searches.length} recipes.
                        </Typography>
                        <Box height={"20px"}/>
                        {this.state.searches.map((recipe, index) => (
                            <div key={index}>
                                <ListItemButton
                                    sx={{
                                        backgroundColor: blue[400]
                                    }}
                                    onClick={() => onRecipeClick(recipe)}
                                >
                                    <ListItemText primary={recipe.ingredients.replace(/,/g, ', ')}/>
                                    <ListItemText primary={`Created at: ${recipe.created_at}`}/>
                                </ListItemButton>
                                <Box height={"5px"}/>
                            </div>
                        ))}
                    </CardContent>
                </Card>
            </div>
        );
    }
}