open BsReactNative;

type state = {
  grid: Life.grid,
  moving: bool,
  colourGrid: Life.colourGrid,
  goNumber: int
};

type action =
  | SwitchItem(int, int)
  | BoardMove
  | ToggleStart;

let component = ReasonReact.reducerComponent("Board");

let styles =
  StyleSheet.create(
    Style.(
      {
        "wrapper":
          style([
            width(Pct(100.0)),
            padding(Pt(10.0)),
            marginTop(Pt(-10.0)),
            backgroundColor("#cccccc")
          ]),
        "text": style([fontSize(Float(16.0)), color("red"), padding(Pt(10.0))])
      }
    )
  );

let initialState = () => {
  grid: Life.makeGrid(false),
  moving: false,
  colourGrid: Life.makeGrid(0),
  goNumber: 0
};

let newGoNumber = goNumber => goNumber > 5 ? goNumber + 1 : 0;

let newBoardMove = state => {
  let newGrid = Life.boardMove(state.grid);
  {
    grid: newGrid,
    moving: Changed.hasChanged(state.grid, newGrid),
    colourGrid: Colours.getColours(newGrid, state.colourGrid),
    goNumber: newGoNumber(state.goNumber)
  };
};

let justColourMove = state => {
  ...state,
  colourGrid: Colours.getColours(state.grid, state.colourGrid)
};

let isMoveTime = goNumber => goNumber === 0;

let boardMove = state =>
  state.moving && isMoveTime(state.goNumber) ?
    newBoardMove(state) : justColourMove(state);

let switchItem = (x, y, state) => {
  let newGrid = Life.reverseItem(state.grid, x, y);
  {
    ...state,
    grid: newGrid,
    colourGrid: Colours.getColours(newGrid, state.colourGrid)
  };
};

let reducer = (action, state) =>
  switch action {
  | SwitchItem(x, y) => ReasonReact.Update(switchItem(x, y, state))
  | BoardMove => ReasonReact.Update(boardMove(state))
  | ToggleStart => ReasonReact.Update({...state, moving: ! state.moving})
  };

let changeSingleItem = (reduce, x, y) => reduce(() => SwitchItem(x, y));

let renderMovingText = moving => moving ? "Stop" : "Start";

let make = _children => {
  ...component,
  subscriptions: self => [
    Sub(
      () => Js.Global.setInterval(self.reduce(() => BoardMove), 30),
      Js.Global.clearInterval
    )
  ],
  initialState,
  reducer,
  render: self =>
    <View style=styles##wrapper>
      <Text style=styles##text onPress=(self.reduce(() => ToggleStart))>
        (ReasonReact.stringToElement(renderMovingText(self.state.moving)))
      </Text>
      <Grid
        grid=self.state.colourGrid
        changeItem=(changeSingleItem(self.reduce))
      />
    </View>
};