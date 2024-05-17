import { React } from './react.js'

//----------------------------------------------------------
// JSX syntax expects Capitalized tags to be functions, so we need to
// add a tralslation for the native UI element tags.
const Label = (props) => { return React.createElement("Label", props); };
const Panel = (props) => { return React.createElement("Panel", props); };

//----------------------------------------------------------
// Components


const LeftPane = (props) => {

    const style = {
        "background-color": "#666600",
        "width": props.width
    };

    return (
        <Panel style={style}>
            <Label text="Left pane" />
            <Label text={props.width + "px"} />
        </Panel>
    )
}

const Separator = (props) => {

    const style = {
        "width": props.dragging ? 6 : 3,
        "background-color": props.dragging ? "red" : "black",
        "cursor": "drag"
    }

    const mouseDown = () => {
        if (props.onDragStart)
            props.onDragStart();
    }

    const mouseUp = () => {
        if (props.dragging && props.onDragStop)
            props.onDragStop();
    }

    return (
        <Panel style={style}
               onmousedown={mouseDown}
               onmouseup={mouseUp} />
    )
}

const RightPane = () => {
    const style = {
        "background-color": "#006666",
        "flex-grow": true
    };

    return (
        <Panel style={style}>
            <Label text="Right pane" />
        </Panel>
    )
}

const VerticalPanel = (props) => {
    const style = {
        "flex-direction": "row",
        "flex-grow": true
    };

    const onDragStart = () => {
        if (props.onDragStart)
            props.onDragStart()
    };

    const onDrag = (event) => {
        if (props.dragging && props.onDrag)
            props.onDrag(event);
    };

    const onDragStop = () => {
        if (props.onDragStop)
            props.onDragStop();
    };

    return (
        <Panel style={style} onmousedrag={onDrag}>
            <LeftPane width={props.leftWidth} />
            <Separator dragging={props.dragging}
                       onDragStart={onDragStart}
                       onDragStop={onDragStop} />
            <RightPane />
        </Panel>
    )
}

var model = {
    prev_width: 200,
    left_width: 200,
    min_width: 70,
    max_width: 450,
    dragging: false
};


const App = () => {

    const update = () => {
        globalThis.render();
    };

    const onDragStart = () => {
        model.prev_width = model.left_width;
        model.dragging = true;
        update();
    };

    const onDrag = (event) => {
        if (model.dragging) {
            model.left_width = model.prev_width + event['drag_x'];

            if (model.left_width < model.min_width)
                model.left_width = model.min_width;
            else if (model.left_width > model.max_width)
                model.left_width = model.max_width;

            update();
        }
    };

    const onDragStop = () => {
        model.dragging = false;
        model.prev_width = model.left_width;
        update();
    };

    return (
        <view>
            <VerticalPanel leftWidth={model.left_width}
                           dragging={model.dragging}
                           onDragStart={onDragStart}
                           onDrag={onDrag}
                           onDragStop={onDragStop} />
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
