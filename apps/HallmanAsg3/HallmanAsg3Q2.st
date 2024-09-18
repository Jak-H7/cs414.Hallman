Model subclass: #Counter
	instanceVariableNames: 'value'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'MVC-Tutorial'!

MouseMenuController subclass: #CounterController
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'MVC-Tutorial'!

View subclass: #CounterView
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'MVC-Tutorial'!

!Counter methodsFor: 'accessing' stamp: 'JH 09/18/2024 15:31'!
value
	"Answer the current value of the receiver"
	^value! !

!Counter methodsFor: 'accessing' stamp: 'JH 09/18/2024 15:32'!
value: aNumber
	"Initialize the counter to value aNumber"
	value := aNumber.
	self changed. "to update displayed value"! !

!Counter methodsFor: 'initialize-release' stamp: 'JH 09/18/2024 15:33'!
initialize
	"Set the initial value to 0."
	self value: 0.! !

!Counter methodsFor: 'operations' stamp: 'JH 09/18/2024 15:34'!
decrement
	"Subtract 1 from the value of the counter"
	self value: value - 1.! !

!Counter methodsFor: 'operations' stamp: 'JH 09/18/2024 15:35'!
increment
	"Add 1 to the value of the counter"
	self value: value + 1.! !

!Counter class methodsFor: 'instance creation' stamp: 'JH 09/18/2024 15:36'!
new
	"Answer an initialized instance of the receiver"
	^super new initialize! !

!CounterController methodsFor: 'control defaults' stamp: 'JH 09/18/2024 15:37'!
isControlActive
	^super isControlActive & sensor blueButtonPressed not! !

!CounterController methodsFor: 'initialize-release' stamp: 'JH 09/18/2024 15:38'!
initialize
	"Initialize a menu of commands for changing the value of the model"
	super initialize.
	self redButtonMenu:
		(PopUpMenu labels: 'increment\decrement' withCRs)
			redButtonMessages: #(increment decrement)! !

!CounterController methodsFor: 'menu messages' stamp: 'JH 09/18/2024 15:39'!
decrement
	"Subtract 1 from the value of the counter"
	self model decrement! !

!CounterController methodsFor: 'menu messages' stamp: 'JH 09/18/2024 15:40'!
increment
	"Add 1 to the value of the counter"
	self model increment! !

!CounterView methodsFor: 'controller access' stamp: 'JH 09/18/2024 15:41'!
defaultControllerClass
	"Answer the class of a typically useful controller"
	^CounterController.! !

!CounterView methodsFor: 'displaying' stamp: 'JH 09/18/2024 15:42'!
displayView
	| box pos displayText |
	box := self insetDisplayBox.
	pos := box origin + (4 @ ((box extent y / 3) rounded)).
	displayText := ('value: ', self model value printString) asDisplayText.
	displayText foregroundColor: Color black.
	displayText backgroundColor: Color white.
	displayText displayAt: pos.! !

!CounterView methodsFor: 'updating' stamp: 'JH 09/18/2024 15:43'!
update: aParameter
	"Simply redisplay everything"
	self display.! !

!CounterView class methodsFor: 'instance creation' stamp: 'JH 09/18/2024 15:44'!
open
	"Open a view for a new counter"
	| aCounterView topView |
	aCounterView := CounterView new model: Counter new.
	aCounterView borderWidth: 2.
	aCounterView insideColor: Color white.
	topView := StandardSystemView new label: 'Counter'.
	topView minimumSize: 80 @ 40; maximumSize: 120 @ 100.
	topView addSubView: aCounterView.
	topView controller open.! !

!CounterView class methodsFor: 'instance creation' stamp: 'JH 09/18/2024 15:45'!
openWithGraphicalButtons
	"Open a view with graphical buttons for a new counter"
	| aCounterView topView incrButton decrButton incrSwitchView decrSwitchView dt textStyle |
	aCounterView := CounterView new model: Counter new.
	aCounterView borderWidthLeft: 1 right: 2 top: 2 bottom: 2.
	aCounterView insideColor: Color white.
	topView := ColorSystemView new label: 'Counter'.
	topView minimumSize: 100 @ 40; maximumSize: 260 @ 220.

	incrButton := Button newOff.
	incrButton onAction: [aCounterView model increment].
	incrSwitchView := PluggableButtonView on: incrButton getState: #isOn action: #turnOn.
	textStyle := (TextStyle named: 'NewYork') copy.
	dt := ('+' asText addAttribute: TextFontChange font4) allBold asDisplayText.
	dt foregroundColor: Color black; backgroundColor: Color lightGreen.
	dt textStyle: textStyle.
	incrSwitchView label: dt.
	incrSwitchView borderWidthLeft: 2 right: 1 top: 2 bottom: 1.
	incrSwitchView insideColor: Color lightGreen.
	incrSwitchView window: (0 @ 0 extent: 40 @ 50).
	topView addSubView: incrSwitchView toLeftOf: aCounterView.

	decrButton := Button newOff.
	decrButton onAction: [aCounterView model decrement].
	decrSwitchView := PluggableButtonView on: decrButton getState: #isOn action: #turnOn.
	dt := ('-' asText addAttribute: TextFontChange font4) allBold asDisplayText.
	dt foregroundColor: Color black; backgroundColor: Color lightRed.
	decrSwitchView label: dt.
	decrSwitchView borderWidthLeft: 2 right: 1 top: 1 bottom: 2.
	decrSwitchView insideColor: Color lightRed.
	decrSwitchView window: (0 @ 0 extent: 40 @ 50).
	aCounterView window: (0 @ 0 extent: 60 @ 100).

	topView addSubView: decrSwitchView below: incrSwitchView.
	topView addSubView: aCounterView toRightOf: incrSwitchView.
	topView controller open.! !

!CounterView class methodsFor: 'instance creation' stamp: 'JH 09/18/2024 15:46'!
openWithSpinner
	"Open a view with a spinner control for a new counter"
	| aCounterView topView spinner |
	aCounterView := CounterView new model: Counter new.
	aCounterView borderWidthLeft: 1 right: 2 top: 2 bottom: 2.
	aCounterView insideColor: Color white.
	topView := ColorSystemView new label: 'Counter'.
	topView minimumSize: 100 @ 40; maximumSize: 260 @ 220.

	spinner := PluggableSpinMorph on: aCounterView model getValueSelector: #value setValueSelector: #value:.
	spinner minValue: 0.
	spinner maxValue: 100.
	spinner step: 1.
	spinner extent: 40 @ 50.
	spinner window: (0 @ 0 extent: 60 @ 50).

	topView addSubView: spinner.
	topView controller open.! !