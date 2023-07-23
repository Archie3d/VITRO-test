globalThis.JSX = (tag, attrs, children) => {

    var element = null;

    if (typeof tag === 'function') {
        element = tag(attrs);
    } else {
        var element = React.createElement(tag, attrs);
    }

    var key = 0;

    children.forEach(child => {
        if (Array.isArray(child)) {
            child.forEach(ch => {
                ch['key'] = key;
                element.children.push(ch);
                key += 1;
            });
        } else {
            child['key'] = key;
            element.children.push(child);
            key += 1;
        }
    });

    return element;
}

export class React {
    static createElement(tag, attrs) {
        return {
            type: tag,
            attributes: attrs,
            children: []
        };
    }

    static reconcileChildren(element, container) {
        var reconciledChildren = [];
        var children = container.children;

        element.children.forEach(child => {
            // Find the original child with the same tag
            var reconciledElement = null;

            for (var i = 0; i < children.length; i++) {
                if (children[i].tagName == child.type) {
                    reconciledElement = children[i];
                    children.splice(i, 1);
                    break;
                }
            }

            if (reconciledElement === null)
                reconciledElement = view.createElement(child.type);

            // Copy attributes
            Object.keys(child.attributes)
                .forEach(name => {
                    reconciledElement.setAttribute(name, child.attributes[name]);
                });

            reconciledChildren.push(reconciledElement);

            // Run reconciliation recursively
            if (child.children !== 'undefined' && child.children.length > 0) {
                React.reconcileChildren(child, reconciledElement);
            }
        });

        container.replaceChildren(reconciledChildren);
    }

}
