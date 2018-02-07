open BsReactNative;

/* next steps - styles to make items into actual grid */
let styles =
  StyleSheet.create(
    Style.(
      {
        "grid":
          style([width(Pct(100.0)), height(Pt(400.0)), flexDirection(Column)]),
        "row": style([flexDirection(Row), flex(1.0)]),
        "item": style([flex(1.0)]),
        "highlight": style([flex(1.0)]),
        "full": style([flex(1.0), backgroundColor("blue")]),
        "empty": style([flex(1.0), backgroundColor("green")])
      }
    )
  );

let component = ReasonReact.statelessComponent("Grid");

let drawFull = <View style=styles##full />;

let drawEmpty = <View style=styles##empty />;

let drawSquare = (valid: bool) => valid ? drawFull : drawEmpty;

let drawItem = (changeItem, y: int, x: int, item: bool) =>
  <View style=styles##item key=(string_of_int(x))>
    <TouchableHighlight style=styles##highlight onPress=(() => changeItem())>
      (drawSquare(item))
    </TouchableHighlight>
    <Text>
      (
        ReasonReact.stringToElement(
          string_of_int(x) ++ ", " ++ string_of_int(y)
        )
      )
    </Text>
  </View>;

let drawRow = (changeItem, y: int, row: list(bool)) =>
  <View style=styles##row key=(string_of_int(y))>
    (
      ReasonReact.arrayToElement(
        Array.mapi(drawItem(changeItem, y), Array.of_list(row))
      )
    )
  </View>;

let make = (~grid, ~changeItem, _children) => {
  ...component,
  render: self => {
    let repoItems =
      ReasonReact.arrayToElement(
        Array.mapi(drawRow(changeItem), Array.of_list(grid))
      );
    <View style=styles##grid> repoItems </View>;
  }
};