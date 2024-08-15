/*  Ingredient - A class to store ingredient information
    Inputs:
        ingredient: An object containing the ingredient information
    Properties:
        ID: The ID of the ingredient
        Amount: The amount of the ingredient
        Unit: The unit of the ingredient
        UnitLong: The long unit of the ingredient
        UnitShort: The short unit of the ingredient
        Aisle: The aisle of the ingredient
        Name: The name of the ingredient
        Original: The original ingredient string
        OriginalName: The original name of the ingredient
        Meta: The meta information of the ingredient
        Image: The URL of the ingredient image
    Methods:
        None
*/
export default class Ingredient {
    constructor(ingredient) {
        this.ID = ingredient.id;
        this.Amount = ingredient.amount;
        this.Unit = ingredient.unit;
        this.UnitLong = ingredient.unitLong;
        this.UnitShort = ingredient.unitShort;
        this.Aisle = ingredient.aisle;
        this.Name = ingredient.name;
        this.Original = ingredient.original;
        this.OriginalName = ingredient.originalName;
        this.Meta = ingredient.meta;
        this.Image = ingredient.image;
    }
}