import { React } from './react.js'

//----------------------------------------------------------
// JSX syntax expects Capitalized tags to be functions, so we need to
// add a tralslation for those to the UI elements.
const Label = (props) => { return React.createElement("Label", props); };
const Panel = (props) => { return React.createElement("Panel", props); };
const TextEditor = (prop) => { return React.createElement("TextEditor", prop); }
const TextButton = (prop) => { return React.createElement("TextButton", prop); }

//----------------------------------------------------------
// Components

const Input = (props) => {

    const editId = "new_item_text_editor";

    const appendRow = () => {
        if (props.onAdd) {
            props.onAdd(view.getElementById(editId).getAttribute("text"));
        }
    }

    return (
        <Panel class="input">
            <TextEditor id={editId} />
            <TextButton text="Add" onclick={appendRow}/>
        </Panel>
    )
}

const Row = (props) => {
    const deleteRow = () => {
        if (props.onDelete) {
            props.onDelete()
        }
    }

    return (
        <Panel class="row">
            <Label class="row" text={props.text} />
            <TextButton class="delete" text="X" onclick={deleteRow}/>
        </Panel>
    )
}

const Table = (props) => {

    const deleteRow = (index) => {
        if (props.onDelete) {
            props.onDelete(index);
        }
    }

    return (
        <Panel class="scroll">
            {props.items.map((item, idx) => {
                return (
                    <Row text={item} onDelete={() => {deleteRow(idx)}}/>
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

    const update = () => {
        //setTimeout(globalThis.render, 0);
        globalThis.render();
    }

    const addRow = (text) => {
        items.push(text);
        update();
    }

    const deleteRow = (index) => {
        items.splice(index, 1);
        update();
    }

    return (
        <view>
            <Input onAdd={addRow} />
            <Table items={items} onDelete={deleteRow} />
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
    view.refresh();
}
