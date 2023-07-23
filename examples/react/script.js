import { React } from './react.js'

//----------------------------------------------------------
// JSX syntax expects Capitalized tags to be functions, so we need to
// add a tralslation for those to the UI elements.
const Label = (props) => {
    return {
        type: "Label",
        attributes: props,
        children: []
    };
};

const Panel = (props) => {
    return {
        type: "Panel",
        attributes: props,
        children: []
    };
};

//----------------------------------------------------------
// Components

const Row = (props) => {
    return (
        <Label text={props.text} />
    )
}

const Table = (props) => {
    return (
        <Panel>
            {props.items.map((item, idx) => {
                return (
                    <Row text={item} />
                )
            })}
        </Panel>
    )
}

//----------------------------------------------------------
// The data model

var items = ["First", "Second", "Third", "Fourth", "Fifth"];

//----------------------------------------------------------
// Top-level application component.
// The root tag returned by this component will be ignored, since
// reconciliation starts at the first children level.
const App = () => {
    return (
        <view>
            <Table items={items} />
        </view>
    )
}

//----------------------------------------------------------
// Render the UI.
// This must be called each time the model changes to rebuild
// the virtual DOM and then reconcile it to the UI elements tree.
globalThis.render = () => {
    var app = App();
    React.reconcileChildren(app, view);
}
