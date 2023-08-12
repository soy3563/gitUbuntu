//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/04/2023 01:39:36 PM
// Design Name: 
// Module Name: lineBuffer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

`timescale 1ns / 1ps

module imgConv(
    input       clk,
    input       rstb,
    input [3:0] swt,
    output [3:0] led
);

`ifdef XSIM_DEF //only for simulation
wire [31:0] w_i_cnt_25M = 32'd25;
wire [31:0] w_i_cnt_50M = 32'd50;
wire [31:0] w_i_cnt_100M = 32'd100;
wire [31:0] w_i_cnt_200M = 32'd200;
`else // implementation
wire [31:0] w_i_cnt_25M = 32'd25000000;
wire [31:0] w_i_cnt_50M = 32'd50000000;
wire [31:0] w_i_cnt_100M = 32'd100000000;
wire [31:0] w_i_cnt_200M = 32'd200000000;
`endif

lineBuffer
cnt_25M
(
    .clk(clk),
    .rstb(rstb),
    .ena(swt[0]),
    .i_cntMax(w_i_cnt_25M),
    .o_toggle(led[0])
);

lineBuffer
cnt_50M
(
    .clk(clk),
    .rstb(rstb),
    .ena(swt[1]),
    .i_cntMax(w_i_cnt_50M),
    .o_toggle(led[1])
);

lineBuffer
cnt_100M
(
    .clk(clk),
    .rstb(rstb),
    .ena(swt[2]),
    .i_cntMax(w_i_cnt_100M),
    .o_toggle(led[2])
);

lineBuffer
cnt_200M
(
    .clk(clk),
    .rstb(rstb),
    .ena(swt[3]),
    .i_cntMax(w_i_cnt_200M),
    .o_toggle(led[3])
);

endmodule