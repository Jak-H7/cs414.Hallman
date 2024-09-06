Object subclass: #TestCaseOf
    instanceVariableNames: ''
    classVariableNames: ''
    poolDictionaries: ''
    category: 'Tests-SUnit'!

!Object methodsFor: 'case handling' stamp: 'JH 9/4/2024 7:15'!
caseOf: caseDict ifAbsent: absentBlock
    "Evaluate the block of code for the matching key. If none match, evaluate the absentBlock."
    ^ (caseDict keys includes: self)
        ifTrue: [ (caseDict at: self) value ]
        ifFalse: [ absentBlock value ].
! !

!TestCaseOf methodsFor: 'testing' stamp: 'JH 9/4/2024 7:16'!
testMatchingCase
    | value result |
    value := 3.
    result := (value caseOf: {
        1 -> [ 'Value is 1' ].
        2 -> [ 'Value is 2' ].
        3 -> [ 'Value is 3' ].
        4 -> [ 'Value is 4' ].
    }) ifAbsent: [ 'Unknown value' ].
    
    self assert: result equals: 'Value is 3'.
! !

!TestCaseOf methodsFor: 'testing' stamp: 'JH 9/4/2024 7:17'!
testAbsentCase
    | value result |
    value := 6.
    result := (value caseOf: {
        1 -> [ 'Value is 1' ].
        2 -> [ 'Value is 2' ].
        3 -> [ 'Value is 3' ].
        4 -> [ 'Value is 4' ].
    }) ifAbsent: [ 'Unknown value' ].
    
    self assert: result equals: 'Unknown value'.
! !