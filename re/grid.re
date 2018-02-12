open BsReactNative;

let styles =
  StyleSheet.create(
    Style.(
      {
        "grid":
          style([width(Pct(100.0)), height(Pt(600.0)), flexDirection(Column)]),
        "row": style([flexDirection(Row), flex(1.0)]),
        "item": style([flex(1.0)]),
        "highlight": style([flex(1.0)])
      }
    )
  );

let component = ReasonReact.statelessComponent("Grid");

let drawSquare = (value: int) =>
  <View
    style=Style.(
            style([
              flex(1.0),
              backgroundColor(Colours.intToColourString(value))
            ])
          )
  />;

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
  render: _self => {
    let repoItems =
      ReasonReact.arrayToElement(
        Array.of_list(List.mapi(drawRow(changeItem), grid))
      );
    <View style=styles##grid> repoItems </View>;
  }
};