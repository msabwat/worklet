class MyWorkletProcessor extends AudioWorkletProcessor {
    constructor(){
        super();
        this.frequency = 440;
        this.n = 0;
    }
    // When constructor() undefined, the default constructor will be
    // implicitly used.
    process(inputs, outputs) {
	// By default, the node has single input and output.
	const input = inputs[0];
	let output = outputs[0];
	
	const outputChannel = output[0];
	const fs = 44100;
	  
	for (let i = 0; i < 128; i++) {
            output = Math.sin((2 * Math.PI * this.frequency * this.n) / fs);
            outputChannel[i] = output;
            this.n++;
	}
	
	/*
	for (let i = 0; i < inputs.length; i++){
		for (let channel = 0; channel < outputs.length; channel++) {
			outputs[i][channel].set(inputs[i][channel]);
		}	
	} 
	*/
	return true;
    }
}
registerProcessor('worklet-processor', MyWorkletProcessor);
