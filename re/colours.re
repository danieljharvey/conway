/* colours.re -> we allow the colours to fade away nicely and that's great */
let getItemColour = (item: bool, colour: int) : int =>
  item ? 100 : max(colour - 10, 0);

let getColours = (grid, colours) =>
  List.map2(
    (gridRow, colourRow) => List.map2(getItemColour, gridRow, colourRow),
    grid,
    colours
  );

let checkBounds = (minValue, maxValue, value) =>
  max(minValue, min(maxValue, value));

let makeBlack = value => value < 20 ? 20 : value;

let makeWhite = value => value > 240 ? 240 : makeBlack(value);

let getColourValue = (value: int) : int =>
  checkBounds(0, 255, makeWhite(255 - Random.int(20) - value * 2));

let intStr = (int: int) : string => string_of_int(getColourValue(int));

let intToColourString = (value: int) : string =>
  "rgb("
  ++ intStr(value)
  ++ ","
  ++ intStr(value)
  ++ ","
  ++ intStr(value)
  ++ ")";