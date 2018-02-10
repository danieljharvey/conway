open BsReactNative;

/* next steps - styles to make items into actual grid */
let styles =
  StyleSheet.create(
    Style.(
      {
        "grid":
          style([width(Pct(100.0)), height(Pt(600.0)), flexDirection(Column)]),
        "row": style([flexDirection(Row), flex(1.0)]),
        "item": style([flex(1.0)]),
        "highlight": style([flex(1.0)]),
        "standard": style([flex(1.0)]),
        "oneHundred": style([flex(1.0), backgroundColor("black")]),
        "ninety": style([flex(1.0), backgroundColor("#AA9977")]),
        "fifty": style([flex(1.0), backgroundColor("#CC99EE")]),
        "ten": style([flex(1.0), backgroundColor("#FFDDEE")]),
        "zero": style([flex(1.0), backgroundColor("white")])
      }
    )
  );

let component = ReasonReact.statelessComponent("Grid");

let drawOneHundred = value =>
  <View
    style=Style.(
            style([
              flex(1.0),
              backgroundColor(Colours.intToColourString(value))
            ])
          )
  />;

let drawNinety = <View style=styles##ninety />;

let drawFifty = <View style=styles##fifty />;

let drawTen = <View style=styles##ten />;

let drawZero = <View style=styles##zero />;

let drawSquare = (value: int) => drawOneHundred(value);

let drawItem = (changeItem, y: int, x: int, item: int) =>
  <View style=styles##item key=(string_of_int(x))>
    <TouchableHighlight style=styles##highlight onPress=(changeItem(x, y))>
      (drawSquare(item))
    </TouchableHighlight>
  </View>;

let drawRow = (changeItem, y: int, row: list(int)) =>
  <View style=styles##row key=(string_of_int(y))>
    (
      ReasonReact.arrayToElement(
        Array.of_list(List.mapi(drawItem(changeItem, y), row))
      )
    )
  </View>;

let make = (~grid, ~changeItem, _children) => {
  ...component,
  render: self => {
    let repoItems =
      ReasonReact.arrayToElement(
        Array.of_list(List.mapi(drawRow(changeItem), grid))
      );
    <View style=styles##grid> repoItems </View>;
  }
};