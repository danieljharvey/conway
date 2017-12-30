open BsReactNative;

type state = {title: string};

type action =
  | Reverse;

let component = ReasonReact.reducerComponent("Board");

let styles =
  StyleSheet.create(
    Style.(
      {
        "wrapper": style([padding(Pt(10.0)), marginTop(Pt(-10.0))]),
        "text": style([fontSize(Float(16.0)), color("red"), padding(Pt(10.0))])
      }
    )
  );

let reverseString = str => str ++ "!";

let make = _children => {
  ...component,
  initialState: () => {title: "horses"},
  reducer: (action, state) =>
    switch action {
    | Reverse => ReasonReact.Update({title: reverseString(state.title)})
    },
  render: self =>
    <View style=styles##wrapper>
      <Text style=styles##text onPress=(self.reduce(() => Reverse))>
        (ReasonReact.stringToElement(self.state.title))
      </Text>
    </View>
};