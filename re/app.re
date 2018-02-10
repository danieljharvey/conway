open BsReactNative;

let styles =
  StyleSheet.create(
    Style.(
      {
        "main":
          style([
            backgroundColor("#665544"),
            flex(1.),
            justifyContent(Center),
            alignItems(Center)
          ])
      }
    )
  );

let app = () => <View style=styles##main> <Board /> </View>;