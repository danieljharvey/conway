open BsReactNative;

/* next steps - styles to make items into actual grid */

let component = ReasonReact.statelessComponent("Grid");

let drawItem = (item: int) =>
    <Text>
        {ReasonReact.stringToElement("Thing")}
    </Text>;

let drawRow = (row: list(int)) =>
    <View>
        {ReasonReact.arrayToElement(
            Array.map(drawItem, Array.of_list(row))
        )}
    </View>;

let make = (~grid, _children) => {
  ...component,
  render: (self) => {
    let repoItems = ReasonReact.arrayToElement(
        Array.map(drawRow, Array.of_list(grid))
    );

    <View>
      {repoItems}
    </View>
  }
};