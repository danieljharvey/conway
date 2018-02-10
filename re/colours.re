/* colours.re -> we allow the colours to fade away nicely and that's great */
let getItemColour = (item: bool, colour: int) : int =>
  item ? 100 : max(colour - 10, 0);

let getColours = (grid, colours) =>
  List.map2(
    (gridRow, colourRow) => List.map2(getItemColour, gridRow, colourRow),
    grid,
    colours
  );

let intStr = (int: int) : string => string_of_int(255 - int * 2);

let intToColourString = (value: int) : string =>
  "rgb("
  ++ intStr(value)
  ++ ","
  ++ intStr(value)
  ++ ","
  ++ intStr(value)
  ++ ")";